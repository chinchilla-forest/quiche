
#include "quiche/test/quic_test_server.h"

namespace quic{

std::unique_ptr<QuicEventLoop> QuicTestServer::CreateEventLoop() {
  return GetDefaultEventLoop()->Create(QuicDefaultClock::Get());
}

bool QuicTestServer::CreateUDPSocketAndListen(const QuicSocketAddress& address) {
  event_loop_ = CreateEventLoop();

  socket_factory_ = std::make_unique<EventLoopSocketFactory>(
      event_loop_.get(), quiche::SimpleBufferAllocator::Get());
  quic_simple_server_backend_->SetSocketFactory(socket_factory_.get());

  QuicUdpSocketApi socket_api;
  fd_ = socket_api.Create(address.host().AddressFamilyToInt(),
                          /*receive_buffer_size =*/kDefaultSocketReceiveBuffer,
                          /*send_buffer_size =*/kDefaultSocketReceiveBuffer);
  if (fd_ == kQuicInvalidSocketFd) {
    QUIC_LOG(ERROR) << "CreateSocket() failed: " << strerror(errno);
    return false;
  }

  overflow_supported_ = socket_api.EnableDroppedPacketCount(fd_);
  socket_api.EnableReceiveTimestamp(fd_);

  bool success = socket_api.Bind(fd_, address);
  if (!success) {
    QUIC_LOG(ERROR) << "Bind failed: " << strerror(errno);
    return false;
  }
  QUIC_LOG(INFO) << "Listening on " << address.ToString();
  port_ = address.port();
  if (port_ == 0) {
    QuicSocketAddress address;
    if (address.FromSocket(fd_) != 0) {
      QUIC_LOG(ERROR) << "Unable to get self address.  Error: "
                      << strerror(errno);
    }
    port_ = address.port();
  }

  bool register_result = event_loop_->RegisterSocket(
      fd_, kSocketEventReadable | kSocketEventWritable, this);
  if (!register_result) {
    return false;
  }
  dispatcher_.reset(CreateQuicDispatcher());
  dispatcher_->InitializeWithWriter(CreateWriter(fd_));

  return true;
}
}
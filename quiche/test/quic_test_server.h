// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef QUCT_TEST_SERVRT_H_
#define QUCT_TEST_SERVRT_H_

// #include "quiche/quic/core/crypto/proof_source.h"
// #include "quiche/quic/tools/quic_simple_server_backend.h"
// #include "quiche/quic/tools/quic_spdy_server_base.h"
// #include "quiche/test/quic_test_server_factory.h"
#include "quiche/quic/core/io/quic_event_loop.h"

namespace quic {

// A binary wrapper for QuicServer.  It listens forever on --port
// (default 6121) until it's killed or ctrl-cd to death.
class QuicTestServer {
 public:
  // A factory for creating QuicSpdyServerBase instances.
    int Start();
    QuicTestServer() = default;
    bool CreateUDPSocketAndListen(const QuicSocketAddress& address);
  // Handles all events. Does not return.
    void HandleEventsForever();
    std::unique_ptr<QuicEventLoop> CreateEventLoop();
  private:
    // ServerFactory* server_factory_;
  std::unique_ptr<QuicEventLoop> event_loop_;
  std::unique_ptr<SocketFactory> socket_factory_;

}  // namespace quic

#endif  // QUICHE_QUIC_TOOLS_QUIC_TOY_SERVER_H_

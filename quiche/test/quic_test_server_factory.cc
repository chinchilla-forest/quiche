#include "quiche/test/quic_test_server_factory.h"
#include "quiche/test/quic_test_server.h"

namespace quic{
    std::unique_ptr<QuicTestServer> QuicServerFactory::CreateServer(){
        return std::make_unique<QuicTestServer>();
    }
}
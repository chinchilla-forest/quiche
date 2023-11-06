

#ifndef QUCT_TEST_SERVRT_FACTORY_H_
#define QUCT_TEST_SERVRT_FACTORY_H_


namespace quic {
class ServerFactory {
   public:
    virtual ~ServerFactory() = default;

    // Creates a QuicSpdyServerBase instance using |backend| for generating
    // responses, and |proof_source| for certificates.
    virtual std::unique_ptr<QuicTestServer> CreateServer() = 0;
  };
// Factory creating QuicServer instances.
class QuicServerFactory : public ServerFactory {
 public:
  std::unique_ptr<QuicTestServer> CreateServer() override;
};

}  // namespace quic

#endif
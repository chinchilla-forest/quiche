// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// A binary wrapper for QuicServer.  It listens forever on --port
// (default 6121) until it's killed or ctrl-cd to death.

#include <vector>

#include "quiche/test/quic_test_server_factory.h"
#include "quiche/quic/platform/api/quic_socket_address.h"


int main(int argc, char* argv[]) {
  quic::QuicServerFactory server_factory;
  auto server = server_factory.CreateServer();

  if (!server->CreateUDPSocketAndListen(quic::QuicSocketAddress(
          quic::QuicIpAddress::Any6(),
          quiche::GetQuicheCommandLineFlag(FLAGS_port)))) {
    return 1;
  }
server->HandleEventsForever();
  return 0;
}

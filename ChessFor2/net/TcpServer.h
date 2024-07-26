#pragma once

#include <atomic>

class TcpServer {
public:
  explicit TcpServer(int port);
  void listen();
  void stop();
  void read(char *buffer, int *sizeBytes) const;

private:
  int m_port;
  bool m_finish;
};

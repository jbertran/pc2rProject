#ifndef __client__
#define __client__
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include "tools.h"

class client {
  int sock;
  struct sockaddr_in serv_addr;
public:
  client(const char* hname, int port);
  int getSocket() { return sock; };
  status handshake(std::string user);
  void terminate();
  void send_message(std::string message);
  std::string recv_message();
};
#endif

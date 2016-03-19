#ifndef __client__
#define __client__
#include "tools.h"

class client {
  int sock;
public:
  client(char* hname, int port);
  int getSocket() { return sock; };
  status handshake(std::string user);
  void terminate();
  void send_message(std::string message);
  std::string recv_message();
};
#endif

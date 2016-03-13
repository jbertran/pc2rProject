#ifndef __client__
#define __client__
#include "tools.h"

int init(char* hname, int port);
status handshake(int sock, std::string user);
void listen(int sock);
void client_terminate();
void send_message(std::string message);

#endif

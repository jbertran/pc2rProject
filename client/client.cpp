#include "client.h"
#include "tools.h"

#define MSG_MAX_SIZE 256

#define CL_DEBUG 1
#ifdef CL_DEBUG
#define cl_debug(str) { std::cout << str << std::endl; }
#else
#define cl_debug(str) ;
#endif

int sock = 0;
struct hostent* server;

client::client(const char* hname, int port) {
  cl_debug("Socket init");
  /* Socket init */
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Socket init error" << std::endl;
    exit(EXIT_FAILURE);
  }
  this->sock = sock;
  
  /* Fill in server address */ 
  memset (&serv_addr, '0', sizeof serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(hname);
  serv_addr.sin_port = htons(port);
  
  /* Connect! */
  if (connect (sock, (struct sockaddr *) &serv_addr, sizeof serv_addr) < 0) {
    std::cerr << "Error connecting" << std::endl;;
    exit(EXIT_FAILURE);
  }
  cl_debug("End socket constr");
}

/**
 * Able to send messages to the server
 * No forbidden messages
 * The server will know which to accept/reject
 * The client GUI will somewhat limit possible values
 */
void client::send_message(std::string message) {
  cl_debug("Sending " + message);
  send(sock, message.c_str(), message.length(), 0);
}

std::string client::recv_message() {
  cl_debug("Receiving...");
  char message [MSG_MAX_SIZE];
  read(sock, message, sizeof message);
  std::string str(message);
  cl_debug("Received!");
  return str;
}

/**
 * Say hello to the server, await ack
 */
status client::handshake(std::string user) {
  cl_debug("Handshake init");
  send_message("CONNEXION/"+user+"/\n");
  std::string await = "BIENVENUE/"+user+"/\n";
  std::string reply = recv_message();
  if (await.compare(reply) == 0) {
    cl_debug("Handshake OK");
    return status::OK;
  }
  else {
    cl_debug("Handshake KO");
    return status::KO;
  }
}

void client::terminate() {
  if (close (this->sock)) 
    std::cerr << "Close error" << std::endl;
}

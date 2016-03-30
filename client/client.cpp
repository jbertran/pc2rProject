#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include "client.h"
#include "tools.h"
#include "session.h"

#define LOCAL

using namespace std;

int sock = 0;
struct hostent* server;

client::client(char* hname, int port) {
  
  /* Socket init */
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    cerr << "Socket init" << endl;
    exit(EXIT_FAILURE);
  }
  this->sock = sock;
  
  /* Fill in server address */ 
  struct sockaddr_in serv_addr;
  memset ((char *) &serv_addr, 0, sizeof serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(hname);
  serv_addr.sin_port = htons(port);
  
  /* Connect! */
  if (connect (sock, (struct sockaddr *) &serv_addr, sizeof serv_addr) < 0) {
    cerr << "Error connecting" << endl;;
    exit(EXIT_FAILURE);
  }
}

/**
 * Able to send messages to the server
 * No forbidden messages
 * The server will know which to accept/reject
 * The client GUI will somewhat limit possible values
 */
void client::send_message(string message) {
  sock_send(this->sock, message);
}

string client::recv_message() {
  return sock_recv(this->sock);
}

/**
 * Say hello to the server, await ack
 */
status client::handshake(string user) {
  sock_send(this->sock, "CONNEXION/"+user);
  string await = "BIENVENUE/"+user;
  string reply = sock_recv(sock);
  if (await.compare(reply) == 0)
    return status::OK;
  else 
    return status::KO;
}

void client::terminate() {
  if (close (this->sock)) 
    cerr << "Close error" << endl;
}

/*
int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Expected hostname and port\n";
    return 1;
  }
  else {
    cout << "Connecting: \n" << "\nNom: " << argv[1] << "Port: " << argv[2] << endl;
    client* inet = new client(argv[1], atoi(argv[2]));
    string username;
    cout << "Username?" << endl;
    cin >> username;
    if (inet->handshake(username) == status::OK) {
      session s = session(inet, username);
      s.start();
    }
    else 
      inet->terminate();
  }
}
*/

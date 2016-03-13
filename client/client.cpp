#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include "client.h"
#include "tools.h"

#define LOCAL

using namespace std;

int sock = 0;
struct hostent* server;
struct sockaddr_in serv_addr;

int init(char* hname, int port) {
  
  /* Socket init */
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    cerr << "Socket init" << endl;
    exit(EXIT_FAILURE);
  }
  
  /* Fill in server address */ 
  memset ((char *) &serv_addr, 0, sizeof serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(hname);
  serv_addr.sin_port = htons(port);
  
  /* Connect! */
  if (connect (sock, (struct sockaddr *) &serv_addr, sizeof serv_addr) < 0) {
    cerr << "Error connecting" << endl;;
    exit(EXIT_FAILURE);
  }
  return sock;
}

/**
 * Able to send messages to the server
 * No forbidden messages
 * The server will know which to accept/reject
 * The client GUI will somewhat limit possible values
 */
void send_message(string message) {
  sock_send(sock, message);
}

/**
 * Say hello to the server, await ack
 */
status handshake(int sock, string user) {
  sock_send(sock, "CONNEX/"+user);
  string await = "BIENVENUE/"+user;
  string reply = *sock_recv(sock);
  if (await.compare(reply) == 0)
    return status::OK;
  else 
    return status::KO;
}

/**
 * Server ack received, operations as normal
 */

void listen(int sock) {
  Phase current_ph = Phase::IDLE;
  bool shouldrun = true;
  while (shouldrun) {
    string msg = *sock_recv(sock);
    vector<string> args = *getArgs(msg);
    switch(current_ph) {
    case Phase::IDLE:
      switch (getCmd(msg)) {
      case Incoming::WELCOME:
	break;
      case Incoming::SESSION:
	break;
      case Incoming::TOUR:
	current_ph = Phase::THINK;
	break;
      default:
	break;
      }
      break;
    case Phase::THINK:
      switch (getCmd(msg)) {
      case Incoming::TUAT:
	break;
      case Incoming::ILAT:
	break;
      case Incoming::FINREF:
	current_ph = Phase::AUCTION;
	break;
      default:
	break;
      }
      break;
    case Phase::AUCTION:
      switch (getCmd(msg)) {
      case Incoming::TUENCH:
	break;
      case Incoming::ECHECENCH:
	break;
      case Incoming::ILENCH:
	break;
      case Incoming::FINENCH:
	current_ph = Phase::SOLVE;
	break;
      default:
	break;
      }
      break;
    case Phase::SOLVE:
      switch (getCmd(msg)) {
      case Incoming::SASOL:
	break;
      case Incoming::BONNE:
	break;
      case Incoming::MAUVAISE:
	break;
      case Incoming::FINRESO:
	break;
      case Incoming::TROPLONG:
	break;
      case Incoming::VAINQ:
	current_ph = Phase::IDLE;
	break;
      default:
	break;
      }
      break;
    default:
      /** Les commandes à écouter quelle que soit la phase**/
      if (getCmd(msg) == Incoming::CONNECTE) {
      }
      else if (getCmd(msg) == Incoming::SORTI) {
      }
      else {
	cerr << "Unexpected message received: " << msg << endl;
      }
    }
  }
}


void client_terminate() {
  if (close (sock)) 
    cerr << "Close error" << endl;
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Expected hostname and port\n";
    return 1;
  }
  else {
    cout << "Connecting: \n" << "\nNom: " << argv[1] << "Port: " << argv[2] << endl;
    int sock = init(argv[1], atoi(argv[2]));
    string username;
    cout << "Username?" << endl;
    cin >> username;
    if (handshake(sock, username) != status::OK)
      client_terminate();
    else {
      listen(sock);
    }
  }
}

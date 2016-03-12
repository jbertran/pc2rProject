#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <unordered_map>
#include "client.h" 

#define MSG_SIZE 1024
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

/****************************************************************************/
/*                                 HELPERS                                  */
/****************************************************************************/

std::unordered_map<string, Incoming> servermsgs = 
  {
    {"BIENVENUE",    Incoming::WELCOME},
    {"CONNECTE",     Incoming::CONNECTE},
    {"SORTI",        Incoming::SORTI},
    {"SESSION",      Incoming::SESSION},
    {"VAINQUEUR",    Incoming::VAINQ},
    {"TOUR",         Incoming::TOUR},
    {"TUASTROUVE",   Incoming::TUAT},
    {"ILATROUVE",    Incoming::ILAT},
    {"FINREFLEXION", Incoming::FINREF},
    {"TUENCHERE",    Incoming::TUENCH},
    {"ECHECENCHERE", Incoming::ECHECENCH},
    {"ILENCHERE",    Incoming::ILENCH},
    {"FINENCHERE",   Incoming::FINENCH},
    {"SASOLUTION",   Incoming::SASOL},
    {"BONNE",        Incoming::BONNE},
    {"MAUVAISE",     Incoming::MAUVAISE},
    {"FINRESO",      Incoming::FINRESO},
    {"TROPLONG",     Incoming::TROPLONG}
  };

vector<string>* split(string msg, char delim) {
  vector<string>* result = new vector<string>();
  string tmp = "";
  while (msg.length() > 0) {
    if (msg[0] == delim) {
      result->push_back(tmp);
      tmp = "";
    }
    else
      tmp = tmp + msg[0];
    msg = msg.substr(1, string::npos);
  }
  if (tmp.length() > 0)
    result->push_back(tmp);
  return result;
}

Incoming getCmd(string msg) {
  vector<string> vect = *split(msg, '/');
  return servermsgs[vect[0]];
}

vector<string>* getArgs(string msg) {
  vector<string>* vect = split(msg, '/');
  return new vector<string>(vect->begin() + 1, vect->end());
}



void sock_send(int sock, string message) {
  if (send(sock, message.c_str(), message.length(), 0) < 0)
    cerr << "Error sending" << message << endl;
}

string* sock_recv(int sock) {
  char* buff = (char*) malloc(MSG_SIZE * sizeof(*buff));
  if (recv(sock, buff, MSG_SIZE, 0) < 0) {
    cerr << "Error receiving message from server" << endl;
    return NULL;
  }
  else
    return new string(buff);
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
hsk handshake(int sock, string user) {
  sock_send(sock, "CONNEX/"+user);
  string await = "BIENVENUE/"+user;
  string reply = *sock_recv(sock);
  if (await.compare(reply) == 0)
    return hsk::OK;
  else 
    return hsk::KO;
}

/**
 * Server ack received, operations as normal
 */

void listen(int sock) {
  Phase current_ph = Phase::IDLE;
  try {
    int i = 0;
    while (i < 10) {
      string msg;
      vector<string> args;
      switch(current_ph) {
      case Phase::IDLE:
	msg = *sock_recv(sock);
	args = *getArgs(msg);
	switch (getCmd(msg)) {
	case Incoming::WELCOME:
	  break;
	case Incoming::CONNECTE:
	  break;
	case Incoming::SORTI:
	  break;
	case Incoming::SESSION:
	  break;
	case Incoming::TOUR:
	  current_ph = Phase::THINK;
	  break;
	}
	break;
      case Phase::THINK:
	msg = *sock_recv(sock);
	args = *getArgs(msg);
	switch (getCmd(msg)) {
	case Incoming::TUAT:
	  break;
	case Incoming::ILAT:
	  break;
	case Incoming::FINREF:
	  current_ph = Phase::AUCTION;
	  break;
	}
	break;
      case Phase::AUCTION:
	msg = *sock_recv(sock);
	args = *getArgs(msg);
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
	}
	break;
      case Phase::SOLVE:
	msg = *sock_recv(sock);
	args = *getArgs(msg);
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
	}
	break;
      default:
	break;
      }
      cout << "lolilol " << i << endl;
      i++;
    }
  } catch (string s) {
    cout << "Disconnect ack'd by server" << endl;
    client_terminate();
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
    if (handshake(sock, username) != hsk::OK)
      client_terminate();
    else {
      listen(sock);
    }
  }
}

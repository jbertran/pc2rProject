#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "client.h"
#include "tools.h"

#define MSG_SIZE 1024

using namespace std;

/** DATA HELPERS **/
unordered_map<string, Incoming> servermsgs = 
  {
    {"BIENVENUE",    Incoming::WELCOME},
    {"CONNECTE",     Incoming::CONNECTE},
    {"SORT",         Incoming::SORTI},
    {"DECONNEXION",  Incoming::DISC},
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

string remove(string msg, char rm) {
  string res = "";
  for (size_t i = 0; i < msg.length(); i++) {
    if (msg[i] != rm)
      res += msg[i];
  }
  return res;
}

vector<string> split(string msg, char delim) {
  vector<string> result;
  string tmp = "";
  while (msg.length() > 0) {
    if (msg[0] == delim) {
      result.push_back(tmp);
      tmp = "";
    }
    else
      tmp = tmp + msg[0];
    msg = msg.substr(1, string::npos);
  }
  if (tmp.length() > 0)
    result.push_back(tmp);
  return result;
}

Incoming getCmd(string msg) {
  vector<string> vect = split(msg, '/');
  return servermsgs[vect[0]];
}

vector<string> getArgs(string msg) {
  vector<string> vect = split(msg, '/');
  return vector<string>(vect.begin() + 1, vect.end());
}

/** INET STUFF **/

void sock_send(int sock, string message) {
  if (send(sock, message.c_str(), message.length(), 0) < 0)
    cerr << "Error sending" << message << endl;
}

string sock_recv(int sock) {
  char* buff = (char*) malloc(MSG_SIZE * sizeof(*buff));
  if (recv(sock, buff, MSG_SIZE, 0) < 0) {
    cerr << "Error receiving message from server" << endl;
    return "";
  }
  else
    return string(buff);
}

/** ENUMS **/
color stocol(char s) {
  unordered_map<char, color> stocol =
    {
      {'R', color::Rouge},
      {'J', color::Jaune},
      {'V', color::Vert},
      {'B', color::Bleu}
    };
  if (stocol.count(s) <= 0) {
    cerr << "Unknown color!" << endl;
    return stocol['R'];
  }
  else
    return stocol[s];
} 

direction stodir(char s) {
  unordered_map<char, direction> stodir = 
    {
      {'H', direction::Haut},
      {'B', direction::Bas},
      {'G', direction::Gauche},
      {'D', direction::Droite}
    };
  if (stodir.count(s) <= 0) {
    cerr << "Unknown direction!" << endl;
    return stodir['H'];
  }
  else
    return stodir[s];
}

char coltos(color c) {
  switch (c) {
  case color::Rouge:
    return 'R';
  case color::Jaune:
    return 'J';
  case color::Vert:
    return 'V';
  case color::Bleu:
    return 'B';
  default:
    cerr << "Unknown color!" << endl;
    return color::Rouge;
  }
} 

char dirtos(direction d) {
  switch (d) {
  case direction::Haut:
    return 'H';
  case direction::Bas:
    return 'B';
  case direction::Gauche:
    return 'G';
  case direction::Droite:
    return 'D';
  default:
    cerr << "Unknown direction!" << endl;
    return direction::Haut;
  }
}

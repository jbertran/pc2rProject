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

/** DATA HELPERS **/
std::unordered_map<std::string, Incoming> servermsgs = 
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
    {"TROPLONG",     Incoming::TROPLONG},
    {"MESSAGE",      Incoming::MSG}
  };

std::string remove(std::string msg, char rm) {
  std::string res = "";
  for (size_t i = 0; i < msg.length(); i++) {
    if (msg[i] != rm)
      res += msg[i];
  }
  return res;
}

std::vector<std::string> split(std::string msg, char delim) {
  std::vector<std::string> result;
  std::string tmp = "";
  while (msg.length() > 0) {
    if (msg[0] == delim) {
      result.push_back(tmp);
      tmp = "";
    }
    else
      tmp = tmp + msg[0];
    msg = msg.substr(1, std::string::npos);
  }
  if (tmp.length() > 0)
    result.push_back(tmp);
  return result;
}

Incoming getCmd(std::string msg) {
  std::vector<std::string> vect = split(msg, '/');
  return servermsgs[vect[0]];
}

std::vector<std::string> getArgs(std::string msg) {
  std::vector<std::string> vect = split(msg, '/');
  return std::vector<std::string>(vect.begin() + 1, vect.end());
}

/** INET STUFF **/

void sock_send(int sock, std::string message) {
  if (send(sock, message.c_str(), message.length(), 0) < 0)
    std::cerr << "Error sending" << message << std::endl;
}

std::string sock_recv(int sock) {
  char* buff = (char*) malloc(MSG_SIZE * sizeof(*buff));
  if (recv(sock, buff, MSG_SIZE, 0) < 0) {
    std::cerr << "Error receiving message from server" << std::endl;
    return "";
  }
  else
    return std::string(buff);
}

/** ENUMS **/
color stocol(char s) {
  std::unordered_map<char, color> stocol =
    {
      {'R', color::Rouge},
      {'J', color::Jaune},
      {'V', color::Vert},
      {'B', color::Bleu}
    };
  if (stocol.count(s) <= 0) {
    std::cerr << "Unknown color!" << std::endl;
    return stocol['R'];
  }
  else
    return stocol[s];
} 

direction stodir(char s) {
  std::unordered_map<char, direction> stodir = 
    {
      {'H', direction::Haut},
      {'B', direction::Bas},
      {'G', direction::Gauche},
      {'D', direction::Droite}
    };
  if (stodir.count(s) <= 0) {
    std::cerr << "Unknown direction!" << std::endl;
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
    std::cerr << "Unknown color!" << std::endl;
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
    std::cerr << "Unknown direction!" << std::endl;
    return direction::Haut;
  }
}

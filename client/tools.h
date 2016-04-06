#ifndef __tools__
#define __tools__

#include <vector>
#include <unordered_map>

enum class status {OK, KO};
enum class Incoming {WELCOME, CONNECTE, DISC, SORTI, VALID, SESSION, VAINQ, TOUR, TUAT, ILAT, FINREF, TUENCH, ECHECENCH, ILENCH, FINENCH, SASOL, BONNE, MAUVAISE, FINRESO, TROPLONG, MSG, UNKNOWN};
enum class Phase {IDLE, THINK, AUCTION, SOLVE};

enum color     { Rouge, Jaune, Vert, Bleu  };
enum direction { Haut, Bas, Droite, Gauche };

typedef struct _coord {
  int x;
  int y;
} coord;

typedef struct _coldir {
  color col;
  direction dir;
} coldir;

typedef struct _move {
  color col;
  direction dir;
  coord depart;
} s_move;

/** UTILS **/
std::vector<std::string> split(std::string msg, char delim);
std::vector<std::string> getArgs(std::string msg);
std::string remove(std::string msg, char rm);
Incoming getCmd(std::string msg);

/** INET **/
void sock_send(int sock, std::string msg);
std::string sock_recv(int sock);

/** Enum helpers **/
color stocol(char s);
direction stodir(char s);
char coltos(color c);
char dirtos(direction d);

#endif

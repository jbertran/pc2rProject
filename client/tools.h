#ifndef __tools__
#define __tools__

enum class status {OK, KO};
enum class Incoming {WELCOME, CONNECTE, SORTI, SESSION, VAINQ, TOUR, TUAT, ILAT, FINREF,
    TUENCH, ECHECENCH, ILENCH, FINENCH, SASOL, BONNE, MAUVAISE, FINRESO, TROPLONG};
enum class Phase {IDLE, THINK, AUCTION, SOLVE};

/** UTILS **/
std::vector<std::string>* split(std::string msg, char delim);
std::vector<std::string>* getArgs(std::string msg);
Incoming getCmd(std::string msg);

/** INET **/
void sock_send(int sock, std::string msg);
std::string* sock_recv(int sock);

#endif

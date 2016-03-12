#ifndef __client__
#define __client__


enum class hsk {OK, KO};

enum class Outgoing {};
enum class Incoming {WELCOME, CONNECTE, SORTI, SESSION, VAINQ, TOUR, TUAT, ILAT, FINREF,
    TUENCH, ECHECENCH, ILENCH, FINENCH, SASOL, BONNE, MAUVAISE, FINRESO, TROPLONG};

enum class Phase {IDLE, THINK, AUCTION, SOLVE};

int init(char* hname, int port);
hsk handshake(int sock, std::string user);
void listen(int sock);
void client_terminate();
void send_message(std::string message);

#endif

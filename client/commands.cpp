#include <iostream>
#include <cstdlib>
#include <vector>
#include "repr.h"
#include "session.h"
#include "client.h"

using namespace std;

/** General messages **/

void session::handleConnectMsg(vector<string> args) {
  string user = args[0];
  cout << user << "s'est connecté." << endl;
}

void session::handleLeftMsg(vector<string> args) {
  string user = args[0];
  cout << user << "a quitté." << endl;  
}

void handleDiscMsg(std::vector<std::string> args) {
  cout << "Confirmation de déconnexion du serveur" << endl;
}

/** Idle Phase Messages **/

// Never used. Welcome is received in the handshake
void session::handleWelcomeMsg(vector<string> args) {
  cout << "Serveur: sup. Ne devrait pas arriver en temps normal" << endl;
}

void session::handleSessionMsg(vector<string> args) {
  string game = args[0];
  vector<string> walls = split(game, ')');
  for (string wall : walls) {
    wall = wall.substr(1, string::npos);
    vector<string> coords = split(wall, ',');
    // Hard-coded for x, y, dir
    this->game->addWall(stoi(coords[0]), 
			stoi(coords[1]), 
			stodir((char)coords[2][0]));
  }
}

vector<coord> parsePuzzle(vector<string> puzzle) {
  vector<coord> res;
  // Hardcoded for groups of coords
  for (size_t i = 0; i < puzzle.size(); i+=2) {
    res.push_back({stoi(puzzle[i]), stoi(puzzle[i+1])});
  }
  return res;
}

void session::handleTurnMsg(vector<string> args) {
  string puzzle = args[0];
  string bilan = args[1];

  // Dpkg the turn's puzzle
  puzzle = puzzle.substr(1, puzzle.length() - 2);
  vector<coord> pos = parsePuzzle(split(puzzle, ','));
  // Set the new robot + target positions
  // Hard-coded for single target
  for (size_t i = 0; i < pos.size() - 1; i++)
    game->setRobot((color) i, pos[i]);
  game->setCible(pos[pos.size() - 1]);

  // Dpkg the score recap for current players
  string tmp = "";
  while (bilan[0] != '(') {
    tmp += bilan[0];
    bilan = bilan.substr(1, string::npos);
  }
  int tour = stoi(tmp);
  cout << "Tour numéro " << tour << endl;

  // Bilan assumed correctly formatted
  bilan = bilan.substr(1, bilan.length() - 2);
  bilan = remove(bilan, ')');
  vector<string> newscores = split(bilan, '(');
  for (string vect : newscores) {
    vector<string> nv = split(vect, ',');
    this->scores[nv[0]] = stoi(nv[1]);
  }
}

void session::handleWinnerMsg(vector<string> args) {
  string user = args[0];
  cout << user << " is the winner!" << endl;
}

/** Thinking Phase Messages **/

void session::handleUFoundMsg(vector<string> args) {
  // ?
  cout << "Confirmation de ma solution par le serveur" << endl;
}

void session::handleHeFoundMsg(vector<string> args) {
  string user = args[0];
  int coups = stoi(args[1]);
  cout << user << " a trouvé une solution en " << coups << " coups." << endl;
}

void session::handleEndThinkMsg(vector<string> args) {
  cout << "Temps écoulé, fin de la phase de réflexion" << endl;
}


/** Auction Phase Messages **/

void session::handleYouBidMsg(vector<string> args) {
  cout << "Validation de mon enchère par le serveur" << endl;
}

void session::handleHeBidsMsg(vector<string> args) {
  string user = args[0];
  int coups = stoi(args[1]);
  cout << user << " a enchéri " << coups << endl;
}

void session::handleFailBidMsg(vector<string> args) {
  string user = args[0];
  cout << "Echec de l'enchère: moins bonne que celle de " << user << endl;
}

void session::handleEndAuctionMsg(vector<string> args) {
  cout << "Temps écoulé, fin de la phase d'enchères" << endl;
}


/** Solving Phase Messages **/

void session::handleHisSolMsg(vector<string> args) {
  string user = args[0];
  string depl = args[1];
  cout << "Solution de " << user << ": " << depl << endl;
  size_t i = 0;
  vector<coldir> dvect;
  while (i < depl.length()) {
    char robot = depl[i];
    char dir = depl[i+1];
    coldir cd;
    cd.col = stocol(robot);
    cd.dir = stodir(dir);
    dvect.push_back(cd);
    i += 2;
  }
  // Do something with dvect
}

void session::handleGoodSolMsg(vector<string> args) {
  cout << "Solution acceptée par le serveur, fin du tour" << endl;
}

void session::handleBadSolMsg(vector<string> args) {
  string user = args[0];
  cout << "Solution rejetée, au tour de " << user << endl;
  if (user.compare(this->username) == 0)
    cout << "A moi!" << endl;
 }

void session::handleEndSolveMsg(vector<string> args) {
  cout << "Fin du tour" << endl;
}

void session::handleTimeoutMsg(vector<string> args) {
  string user = args[0];
  cout << "Timeout du joueur précédent. Nouveau joueur actif: " << user << endl;
  if (user.compare(this->username) == 0)
    cout << "A moi!" <<endl;
}

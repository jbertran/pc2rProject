#include <iostream>
#include <cstdlib>
#include <vector>
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

/** Idle Phase Messages **/

// Never used. Welcome is received in the handshake
void session::handleWelcomeMsg(vector<string> args) {
  
}

void session::handleSessionMsg(vector<string> args) {
  string game = args[0];
}

void session::handleTurnMsg(vector<string> args) {
  string enigme = args[0];
  string bilan = args[1];
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
}

void session::handleGoodSolMsg(vector<string> args) {
  cout << "Solution acceptée par le serveur, fin du tour" << endl;
}

void session::handleBadSolMsg(vector<string> args) {
  string user = args[0];
  cout << "Solution rejetée, au tour de " << user << endl;
 }

void session::handleEndSolveMsg(vector<string> args) {
  cout << "Fin du tour" << endl;
}

void session::handleTimeoutMsg(vector<string> args) {
  string user = args[0];
  cout << "Timeout du joueur précédent. Nouveau joueur actif: " << user << endl;
}

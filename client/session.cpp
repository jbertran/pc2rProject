#include <iostream>
#include "session.h"
#include "client.h"
#include "tools.h"

using namespace std;

session::session(client* c, string user) {
  connexion = c;
  username = user;
  game = new repr();
  scores = unordered_map<string, int>();
}

void session::start() {
  Phase current_ph = Phase::IDLE;
  bool shouldrun = true;
  while (shouldrun) {
    string msg = connexion->recv_message();
    vector<string> args = getArgs(msg);

    /** General commands **/
    switch (getCmd(msg)) {
    case Incoming::CONNECTE:
      handleConnectMsg(args);
      break;
    case Incoming::SORTI:
      handleLeftMsg(args);
      break;
    case Incoming::DISC:
      handleDiscMsg(args);
      shouldrun = false;
      break;
    case Incoming::VAINQ:
      handleWinnerMsg(args);
      break;
    default:
      break;
    }

    /** Phase-dependent commands **/
    switch(current_ph) {
    case Phase::IDLE:
      switch (getCmd(msg)) {
      case Incoming::WELCOME:
	handleWelcomeMsg(args);
	break;
      case Incoming::SESSION:
	handleSessionMsg(args);
	break;
      case Incoming::TOUR:
	current_ph = Phase::THINK;
	handleTurnMsg(args);
	break;
      default:
	break;
      }
      break;
    case Phase::THINK:
      switch (getCmd(msg)) {
      case Incoming::TUAT:
	handleUFoundMsg(args);
	current_ph = Phase::AUCTION;
	break;
      case Incoming::ILAT:
	handleHeFoundMsg(args);
	current_ph = Phase::AUCTION;
	break;
      case Incoming::FINREF:
	handleEndThinkMsg(args);
	current_ph = Phase::AUCTION;
	break;
      default:
	break;
      }
      break;
    case Phase::AUCTION:
      switch (getCmd(msg)) {
      case Incoming::TUENCH:
	handleYouBidMsg(args);
	break;
      case Incoming::ECHECENCH:
	handleFailBidMsg(args);
	break;
      case Incoming::ILENCH:
	handleHeBidsMsg(args);
	break;
      case Incoming::FINENCH:
	handleEndAuctionMsg(args);
	current_ph = Phase::SOLVE;
	break;
      default:
	break;
      }
      break;
    case Phase::SOLVE:
      switch (getCmd(msg)) {
      case Incoming::SASOL:
	handleHisSolMsg(args);
	current_ph = Phase::IDLE;
	break;
      case Incoming::BONNE:
	handleGoodSolMsg(args);
	current_ph = Phase::IDLE;
	break;
      case Incoming::MAUVAISE:
	handleBadSolMsg(args);
	break;
      case Incoming::FINRESO:
	handleEndSolveMsg(args);
	current_ph = Phase::IDLE;
	break;
      case Incoming::TROPLONG:
	handleTimeoutMsg(args);
	current_ph = Phase::IDLE;
	break;
      default:
	break;
      }
      break;
    default:
      break;
    }
  }
}

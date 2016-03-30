#ifndef __session__
#define __session__

#include <unordered_map>
#include <vector>
#include "repr.h"
#include "client.h"

class session {
  client* connexion;
  repr* game;
  //Ui::GUI* gui;
  int tours;
  std::string username;
  std::unordered_map<std::string, int> scores;
public:
  session(client* c, std::string u);
  void start();
  
  /** General messages **/
  void handleConnectMsg(std::vector<std::string> args);
  void handleLeftMsg(std::vector<std::string> args);
  void handleDiscMsg(std::vector<std::string> args);

  /** Idle Phase Messages **/
  void handleWelcomeMsg(std::vector<std::string> args);
  void handleSessionMsg(std::vector<std::string> args);
  void handleTurnMsg(std::vector<std::string> args);
  void handleWinnerMsg(std::vector<std::string> args);

  /** Thinking Phase Messages **/
  void handleUFoundMsg(std::vector<std::string> args);
  void handleHeFoundMsg(std::vector<std::string> args);
  void handleEndThinkMsg(std::vector<std::string> args);

  /** Auction Phase Messages **/
  void handleYouBidMsg(std::vector<std::string> args);
  void handleHeBidsMsg(std::vector<std::string> args);
  void handleFailBidMsg(std::vector<std::string> args);
  void handleEndAuctionMsg(std::vector<std::string> args);

  /** Solving Phase Messages **/
  void handleHisSolMsg(std::vector<std::string> args);
  void handleGoodSolMsg(std::vector<std::string> args);
  void handleBadSolMsg(std::vector<std::string> args);
  void handleEndSolveMsg(std::vector<std::string> args);
  void handleTimeoutMsg(std::vector<std::string> args);
};

#endif

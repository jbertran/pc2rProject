#ifndef __qsession__
#define __qsession__

#include <QThread>
#include <unordered_map>
#include "tools.h"
#include "client.h"
#include "repr.h"
#include "gui.h"

class GUI;

class qSessionThread : public QThread {

  Q_OBJECT

public:
  explicit qSessionThread(client* clt, QObject* parent = 0);

protected:
  void run();

signals:
  /** General messages **/
  void handleConnectMsg(std::vector<std::string> args);
  void handleLeftMsg(std::vector<std::string> args);
  void handleDiscMsg(std::vector<std::string> args);
  void handleChatMsg(std::vector<std::string> args);

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

private:
  client* connexion;
};

#endif

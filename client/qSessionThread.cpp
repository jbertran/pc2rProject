#include "qSessionThread.h"

#define ST_DEBUG 1

#ifdef ST_DEBUG
#define st_debug(str) { std::cout << str << std::endl; }
#else
#define st_debug(str) ;
#endif

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<std::string>)

qSessionThread::qSessionThread(client* clt, QObject* parent) :
  QThread(parent),
  connexion(clt)
{
  qRegisterMetaType<std::string>();
  qRegisterMetaType<std::vector<std::string>>();
  QObject::connect(this, SIGNAL(finished()), this, SLOT(quit()));
}

void qSessionThread::run() {
  st_debug("Run phase");
  Phase current_ph = Phase::IDLE;
  bool shouldrun = true;
  while (shouldrun) {
    /** Await message, then parse it and run the command **/
    std::string msg = connexion->recv_message();
    std::vector<std::string> args = getArgs(msg);

    /** General commands **/
    switch (getCmd(msg)) {
    case Incoming::CONNECTE:
      st_debug("CONNECTE received");
      emit handleConnectMsg(args);
      break;
    case Incoming::SORTI:
      st_debug("SORTI received");
      emit handleLeftMsg(args);
      break;
    case Incoming::DISC:
      st_debug("DISC received");
      emit handleDiscMsg(args);
      shouldrun = false;
      break;
    case Incoming::VAINQ:
      st_debug("VAINQ received");
      emit handleWinnerMsg(args);
      break;
    case Incoming::MSG:
      st_debug("MSG received");
      emit handleChatMsg(args);
      break;
    default:
      break;
    }

    /** Phase-dependent commands **/
    switch(current_ph) {
    case Phase::IDLE:
      switch (getCmd(msg)) {
      case Incoming::WELCOME:
	st_debug("WELCOME received");
	emit handleWelcomeMsg(args);
	break;
      case Incoming::SESSION:
	st_debug("SESSION received");
	emit handleSessionMsg(args);
	break;
      case Incoming::TOUR:
	st_debug("TOUR received");
	current_ph = Phase::THINK;
	emit handleTurnMsg(args);
	break;
      default:
	break;
      }
      break;
    case Phase::THINK:
      switch (getCmd(msg)) {
      case Incoming::TUAT:
	st_debug("TUASTROUVE received");
	emit handleUFoundMsg(args);
	current_ph = Phase::AUCTION;
	break;
      case Incoming::ILAT:
	st_debug("ILATROUVE received");
	emit handleHeFoundMsg(args);
	current_ph = Phase::AUCTION;
	break;
      case Incoming::FINREF:
	st_debug("FINREFLEXION received");
	emit handleEndThinkMsg(args);
	current_ph = Phase::AUCTION;
	break;
      default:
	break;
      }
      break;
    case Phase::AUCTION:
      switch (getCmd(msg)) {
      case Incoming::TUENCH:
	st_debug("TUENCH received");
	emit handleYouBidMsg(args);
	break;
      case Incoming::ECHECENCH:
	st_debug("ECHECENCH received");
	emit handleFailBidMsg(args);
	break;
      case Incoming::ILENCH:
	st_debug("ILENCH received");
	emit handleHeBidsMsg(args);
	break;
      case Incoming::FINENCH:
	st_debug("FINENCH received");
	emit handleEndAuctionMsg(args);
	current_ph = Phase::SOLVE;
	break;
      default:
	break;
      }
      break;
    case Phase::SOLVE:
      switch (getCmd(msg)) {
      case Incoming::SASOL:
	st_debug("SASOLUTION received");
	emit handleHisSolMsg(args);
	current_ph = Phase::IDLE;
	break;
      case Incoming::BONNE:
	st_debug("BONNE received");
	emit handleGoodSolMsg(args);
	current_ph = Phase::IDLE;
	break;
      case Incoming::MAUVAISE:
	st_debug("MAUVAISE received");
	emit handleBadSolMsg(args);
	break;
      case Incoming::FINRESO:
	st_debug("FINRESO received");
	emit handleEndSolveMsg(args);
	current_ph = Phase::IDLE;
	break;
      case Incoming::TROPLONG:
	st_debug("TROPLONG received");
	emit handleTimeoutMsg(args);
	current_ph = Phase::IDLE;
	break;
      default:
	break;
      }
      break;
    default:
      emit handleUnknownMessage(msg);
      break;
    }
  }
}

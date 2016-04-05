#ifndef GUI_H
#define GUI_H

#include "client.h"
#include "repr.h"
#include "qSessionThread.h"
#include "tools.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QLayout>
#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <iostream>

namespace Ui {
  class GUI;
}

class qSessionThread;

class GUI : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit GUI(const char* hname, int port, QWidget *parent = 0);
  void recvMsg(std::string user, std::string msg);
  void sendChatMsg(std::string c);
  void consoleMsg(std::string msg);
  ~GUI();

public slots:
  void hskDone();
  void gui_handleConnectMsg(std::vector<std::string> args);
  void gui_handleLeftMsg(std::vector<std::string> args);
  void gui_handleDiscMsg(std::vector<std::string> args);
  void gui_handleChatMsg(std::vector<std::string> args);

  /** Idle Phase Messages **/
  void gui_handleWelcomeMsg(std::vector<std::string> args);
  void gui_handleSessionMsg(std::vector<std::string> args);
  void gui_handleTurnMsg(std::vector<std::string> args);
  void gui_handleWinnerMsg(std::vector<std::string> args);

  /** Thinking Phase Messages **/
  void gui_handleUFoundMsg(std::vector<std::string> args);
  void gui_handleHeFoundMsg(std::vector<std::string> args);
  void gui_handleEndThinkMsg(std::vector<std::string> args);

  /** Auction Phase Messages **/
  void gui_handleYouBidMsg(std::vector<std::string> args);
  void gui_handleHeBidsMsg(std::vector<std::string> args);
  void gui_handleFailBidMsg(std::vector<std::string> args);
  void gui_handleEndAuctionMsg(std::vector<std::string> args);

  /** Solving Phase Messages **/
  void gui_handleHisSolMsg(std::vector<std::string> args);
  void gui_handleGoodSolMsg(std::vector<std::string> args);
  void gui_handleBadSolMsg(std::vector<std::string> args);
  void gui_handleEndSolveMsg(std::vector<std::string> args);
  void gui_handleTimeoutMsg(std::vector<std::string> args);

private:
  /* Vars à conserver pour fonctionnement */
  Ui::GUI *ui;
  client* guiClient;
  std::unordered_map<std::string, int> scores;
  repr* guiRepr;
  
  /* Vars QT à conserver */
  QStackedWidget* stack;
  QWidget* gameLayout;
  QWidget* hskLayout;
  QLineEdit* hsk_uname;
  QLineEdit* chat;
  QTextEdit* console;
  QTextEdit* chatwind;
  std::string username;
  void setupThreadConnections(qSessionThread* thr);
  void setupHsk();
  void setupGame();
  void switch2Frame(QWidget* frame);
};

/**
 * QLabel de gestion du score.
 * Slots reset(), incr(), decr().
 */

class CoupsLabel : public QLabel
{

  Q_OBJECT

public:
  explicit CoupsLabel(QString text, QWidget* parent);
public slots:
  void reset();
  void incr();
  void decr();
signals:
  void value(int val);
};

#endif // GUI_H

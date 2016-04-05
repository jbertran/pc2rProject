#include "gui.h"
#include "ui_gui.h"
#include "plateauWidget.h"
#include "qSessionThread.h"
#include "robot.h"
#include "repr.h"

#define UI_DEBUG 1
#ifdef UI_DEBUG
#define ui_debug(str) { std::cout << str << std::endl; }
#else
#define ui_debug(str) ;
#endif

class session;
class PlateauWidget;
class Robot;

GUI::GUI(const char* hname, int port, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::GUI),
  guiClient(new client(hname, port)),
  guiRepr(new repr)
{
  ui->setupUi(this);
  stack = new QStackedWidget(this);
  scores = std::unordered_map<std::string, int>();
  setCentralWidget(stack);
  setupHsk();
  setupGame();
  stack->addWidget(hskLayout);
}

void GUI::setupThreadConnections(qSessionThread* thr){
  ui_debug("Setting up thread connections");
  QObject::connect(thr, SIGNAL(handleConnectMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleConnectMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleLeftMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleLeftMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleDiscMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleDiscMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleChatMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleChatMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleWelcomeMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleWelcomeMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleSessionMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleSessionMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleTurnMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleTurnMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleWinnerMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleWinnerMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleUFoundMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleUFoundMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleHeFoundMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleHeFoundMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleEndThinkMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleEndThinkMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleYouBidMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleYouBidMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleHeBidsMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleHeBidsMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleFailBidMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleFailBidMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleEndAuctionMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleEndAuctionMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleHisSolMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleHisSolMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleGoodSolMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleGoodSolMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleBadSolMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleBadSolMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleEndSolveMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleEndSolveMsg(std::vector<std::string>)));
  QObject::connect(thr, SIGNAL(handleTimeoutMsg(std::vector<std::string>)), this,
		   SLOT(gui_handleTimeoutMsg(std::vector<std::string>)));
}

void GUI::setupHsk() {
  hskLayout = new QWidget;
  QLayout* handshake = new QVBoxLayout;
  QLabel* lbl = new QLabel("Nom:");
  hsk_uname = new QLineEdit;
  QPushButton* button = new QPushButton("Connexion");
  QObject::connect(button, SIGNAL(clicked()), this, SLOT(hskDone()));
  handshake->addWidget(lbl);
  handshake->addWidget(hsk_uname);
  handshake->addWidget(button);
  hskLayout->setLayout(handshake);
}

void GUI::hskDone() {
  std::string uname = hsk_uname->text().toStdString();
  ui_debug("hsk done with name " + uname);
  if (uname.compare("") != 0) {
    username = uname;
    switch2Frame(gameLayout);
    guiClient->handshake(username);
    ui_debug("New session..");
    // Starting a new Session thread
    qSessionThread* session = new qSessionThread(guiClient);
    setupThreadConnections(session);
    session->start();
    ui_debug("Done");
  }
}

void GUI::switch2Frame(QWidget* frame) {
  QWidget* del = stack->currentWidget();
  stack->addWidget(frame);
  stack->removeWidget(del);
}

void GUI::recvMsg(std::string user, std::string msg) {
  std::string newline = user+": "+msg;
  chatwind->append(QString::fromUtf8(newline.c_str()));
}

void GUI::consoleMsg(std::string msg) {
  console->append(QString::fromUtf8(msg.c_str()));
}

void GUI::sendChatMsg(std::string msg) {
  std::string send = "MESSAGE/" + msg + "/\n";
  guiClient->send_message(send);
}

void GUI::setupGame() {
  QLayout* mainLayout = new QVBoxLayout;
  // Game Screen
  QLayout * gameScreen = new QHBoxLayout;
  mainLayout->addItem(gameScreen);
  // Plateau
  PlateauWidget* p = new PlateauWidget;
  p->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  gameScreen->addWidget(p);
  // Sidepanel
  QLayout* sidePanel = new QHBoxLayout;
  mainLayout->addItem(sidePanel);
  // Widget de comptage de coups:
  QLayout* coupsLayout = new QHBoxLayout;
  QLabel* coupsText = new QLabel("Nombre de coups: ", p);
  CoupsLabel* coups = new CoupsLabel(QString::number(0), p);
  QObject::connect(p, SIGNAL(counterIncr()), coups, SLOT(incr()));
  QObject::connect(p, SIGNAL(counterDecr()), coups, SLOT(decr()));
  QObject::connect(p, SIGNAL(counterReset()), coups, SLOT(reset()));
  coupsLayout->addWidget(coupsText);
  coupsLayout->addWidget(coups);
  sidePanel->addItem(coupsLayout);
  // Boutons reset, undo, valider
  QPushButton* undo = new QPushButton("Annuler");
  QPushButton* reset = new QPushButton("Tout annuler");
  QPushButton* valid = new QPushButton("Valider");
  QPushButton* ench = new QPushButton(QString::fromUtf8("Enchérir"));
  QObject::connect(valid, SIGNAL(clicked()), p, SLOT(valider()));
  QObject::connect(undo, SIGNAL(clicked()), p, SLOT(undo()));
  QObject::connect(reset, SIGNAL(clicked()), p, SLOT(reset()));
  sidePanel->addWidget(valid);
  sidePanel->addWidget(undo);
  sidePanel->addWidget(reset);
  sidePanel->addWidget(ench);
  // Widget de chat et console
  QLayout* dispLayout = new QVBoxLayout;
  QLayout* chatLayout = new QVBoxLayout;
  console = new QTextEdit;
  chatwind = new QTextEdit;
  chat = new QLineEdit;
  chatwind->setReadOnly(true);
  console->setReadOnly(true);
  chatLayout->addWidget(chatwind);
  chatLayout->addWidget(chat);
  dispLayout->addItem(chatLayout);
  dispLayout->addWidget(console);
  gameScreen->addItem(dispLayout);
    
  gameLayout = new QWidget;
  gameLayout->setLayout(mainLayout);
}

GUI::~GUI()
{
  delete ui;
}

/****************************************************/
/*             GUI QTHREAD INTERACTION              */
/****************************************************/

/** General messages **/

void GUI::gui_handleConnectMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling connectmsg");
  consoleMsg("User "+user+" connected.");
}

void GUI::gui_handleLeftMsg(std::vector<std::string> args) {
    ui_debug("handling leftmsg");
  std::string user = args[0];
  consoleMsg("User "+user+" left.");
}

void GUI::gui_handleDiscMsg(std::vector<std::string> args) {
  std::cout << "Confirmation de déconnexion du serveur" << std::endl;
  ui_debug("handling discmsg");
}

void GUI::gui_handleChatMsg(std::vector<std::string> args) {
  std::string user = args[0];
  std::string msg = args[1];
  ui_debug("handling chatmsg");
  recvMsg(user, msg);
  consoleMsg("Received chat message");
}

/** Idle Phase Messages **/

// Never used. Welcome is received in the handshake
void GUI::gui_handleWelcomeMsg(std::vector<std::string> args) {
  ui_debug("handling welcomemsg");
  std::cout << "Serveur: sup. Ne devrait pas arriver en temps normal" << std::endl;
}

void GUI::gui_handleSessionMsg(std::vector<std::string> args) {
  std::string game = args[0];
  std::vector<std::string> walls = split(game, ')');
  walls.pop_back(); // Remove the trailing empty string
  ui_debug("handling sessionmsg");
  for (std::string wall : walls) {
    wall = wall.substr(1, std::string::npos);
    std::vector<std::string> coords = split(wall, ',');
    // Hard-coded for x, y, dir
    this->guiRepr->addWall(stoi(coords[0]), 
			   stoi(coords[1]), 
			   stodir((char)coords[2][0]));
  }
  consoleMsg("Server provided new game board.");
}

std::vector<coord> parsePuzzle(std::vector<std::string> puzzle) {
  std::vector<coord> res;
  // Hardcoded for groups of coords
  for (size_t i = 0; i < puzzle.size(); i+=2) {
    res.push_back({stoi(puzzle[i]), stoi(puzzle[i+1])});
  }
  return res;
}

void GUI::gui_handleTurnMsg(std::vector<std::string> args) {
  std::string puzzle = args[0];
  std::string bilan = args[1];
  ui_debug("handling turnmsg");
  // Dpkg the turn's puzzle
  puzzle = puzzle.substr(1, puzzle.length() - 2);
  std::vector<coord> pos = parsePuzzle(split(puzzle, ','));
  // Set the new robot + target positions
  // Hard-coded for single target
  for (size_t i = 0; i < pos.size() - 1; i++)
    guiRepr->setRobot((color) i, pos[i]);
  guiRepr->setCible(pos[pos.size() - 1]);
  
  // Dpkg the score recap for current players
  std::string tmp = "";
  while (bilan[0] != '(') {
    tmp += bilan[0];
    bilan = bilan.substr(1, std::string::npos);
  }
  int tour = stoi(tmp);
  std::cout << "Tour numéro " << tour << std::endl;

  // Bilan assumed correctly formatted
  bilan = bilan.substr(1, bilan.length() - 2);
  bilan = remove(bilan, ')');
  std::vector<std::string> newscores = split(bilan, '(');
  for (std::string vect : newscores) {
    std::vector<std::string> nv = split(vect, ',');
    this->scores[nv[0]] = stoi(nv[1]);
  }
  consoleMsg("Server provided new turn description.");
}

void GUI::gui_handleWinnerMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling winnermsg");
  std::cout << user << " is the winner!" << std::endl;
  consoleMsg("Winner: "+user);
}

/** Thinking Phase Messages **/

void GUI::gui_handleUFoundMsg(std::vector<std::string> args) {
  ui_debug("handling ufoundmsg");
  consoleMsg("Your solution was confirmed!");
}

void GUI::gui_handleHeFoundMsg(std::vector<std::string> args) {
  std::string user = args[0];
  int coups = stoi(args[1]);
  ui_debug("handling hefoundmsg");
  consoleMsg("User "+user+" found a solution in "+std::to_string(coups)+"moves.");
}

void GUI::gui_handleEndThinkMsg(std::vector<std::string> args) {
  ui_debug("handling endthinkmsg");
  consoleMsg("End of thinking phase.");
}


/** Auction Phase Messages **/

void GUI::gui_handleYouBidMsg(std::vector<std::string> args) {
  ui_debug("handling youthinkmsg");
  consoleMsg("Your bid was confirmed by the server.");
}

void GUI::gui_handleHeBidsMsg(std::vector<std::string> args) {
  std::string user = args[0];
  int coups = stoi(args[1]);
  ui_debug("handling hebidsmsg");
  consoleMsg("User "+user+" bid "+std::to_string(coups)+"moves");
}

void GUI::gui_handleFailBidMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling failbidmsg");
  consoleMsg("User "+user+"\'s bid failed");
}

void GUI::gui_handleEndAuctionMsg(std::vector<std::string> args) {
  ui_debug("handling endauctionmsg");
  consoleMsg("End of auction phase");
}


/** Solving Phase Messages **/

void GUI::gui_handleHisSolMsg(std::vector<std::string> args) {
  std::string user = args[0];
  std::string depl = args[1];
  ui_debug("handling hissolmsg");
  size_t i = 0;
  std::vector<coldir> dvect;
  while (i < depl.length()) {
    char robot = depl[i];
    char dir = depl[i+1];
    coldir cd;
    cd.col = stocol(robot);
    cd.dir = stodir(dir);
    dvect.push_back(cd);
    i += 2;
  }
  consoleMsg("Displaying user "+user+"\'s solution...");
}

void GUI::gui_handleGoodSolMsg(std::vector<std::string> args) {
  ui_debug("handling goodsolmsg");
  consoleMsg("Solution accepted!");
}

void GUI::gui_handleBadSolMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling badsolmsg");
  std::cout << "Solution rejetée, au tour de " << user << std::endl;
  if (user.compare(this->username) == 0)
    consoleMsg("Your solution was rejected. Your turn.");
  else
    consoleMsg("Solution rejected. Next user: " + user);
}

void GUI::gui_handleEndSolveMsg(std::vector<std::string> args) {
  ui_debug("handling endsolvemsg");
  std::cout << "Fin du tour" << std::endl;
  consoleMsg("End of solution phase");
}

void GUI::gui_handleTimeoutMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling timeoutmsg");
  std::cout << "Timeout du joueur précédent. Nouveau joueur actif: " << user << std::endl;
  if (user.compare(this->username) == 0)
    consoleMsg("My turn to offer a solution");
  else 
    consoleMsg("User "+user+"'s turn to offer a solution");
}


CoupsLabel::CoupsLabel(QString text, QWidget* parent) :
  QLabel(text, parent)
{
}

void CoupsLabel::reset() {
  setText(QString::number(0));
}

void CoupsLabel::incr() {
  setText(QString::number(text().toInt() + 1));
}

void CoupsLabel::decr() {
  setText(QString::number(text().toInt() - 1));
}

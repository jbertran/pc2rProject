#include "gui.h"
#include "ui_gui.h"
#include "plateauWidget.h"
#include "qSessionThread.h"
#include "robot.h"
#include "repr.h"

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
  guiClient(new client(hname, port))
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
  QObject::connect(thr, SIGNAL(handleUnknownMessage(std::string)), this,
		   SLOT(gui_handleUnknownMessage(std::string)));
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
  QObject::connect(thr, SIGNAL(handleValidBid(std::vector<std::string>)), this, 
		   SLOT(gui_handleValidBid(std::vector<std::string>)));
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


void GUI::setupGame() {
  QLayout* mainLayout = new QVBoxLayout;
  // Game Screen
  QLayout * gameScreen = new QHBoxLayout;
  mainLayout->addItem(gameScreen);
  // Plateau
  plateau = new PlateauWidget;
  plateau->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  QObject::connect(plateau, SIGNAL(sendMoves(std::string)), this, SLOT(clientSendMoves(std::string)));
  QObject::connect(this, SIGNAL(resetBoard()), plateau, SLOT(resetRepr()));
  QObject::connect(this, SIGNAL(updateBoard()), plateau, SLOT(update()));
  QObject::connect(this, SIGNAL(addWallBoard(int, int, direction)), 
		   plateau, SLOT(addWallRepr(int, int, direction)));
  gameScreen->addWidget(plateau);
  // Sidepanel
  QLayout* sidePanel = new QHBoxLayout;
  mainLayout->addItem(sidePanel);
  // Widget de comptage de coups:
  QLayout* coupsLayout = new QHBoxLayout;
  QLabel* coupsText = new QLabel("Nombre de coups: ", plateau);
  CoupsLabel* coups = new CoupsLabel(QString::number(0), plateau);
  QObject::connect(plateau, SIGNAL(counterIncr()), coups, SLOT(incr()));
  QObject::connect(plateau, SIGNAL(counterDecr()), coups, SLOT(decr()));
  QObject::connect(plateau, SIGNAL(counterReset()), coups, SLOT(reset()));
  coupsLayout->addWidget(coupsText);
  coupsLayout->addWidget(coups);
  sidePanel->addItem(coupsLayout);
  // Boutons reset, undo, valider
  QPushButton* undo = new QPushButton("Annuler");
  QPushButton* reset = new QPushButton("Tout annuler");
  validB = new QPushButton("Valider");
  foundB = new QPushButton(trUtf8("Trouvé"));
  enchB = new QPushButton(trUtf8("Enchérir"));
  enchB->setDisabled(true);
  QObject::connect(foundB, SIGNAL(clicked()), this, SLOT(trouve()));
  QObject::connect(enchB, SIGNAL(clicked()), this, SLOT(encherir()));
  QObject::connect(validB, SIGNAL(clicked()), plateau, SLOT(valider()));
  QObject::connect(undo, SIGNAL(clicked()), plateau, SLOT(undo()));
  QObject::connect(reset, SIGNAL(clicked()), plateau, SLOT(reset()));
  sidePanel->addWidget(foundB);
  sidePanel->addWidget(validB);
  sidePanel->addWidget(undo);
  sidePanel->addWidget(reset);
  sidePanel->addWidget(enchB);
  // Widget de chat et console
  QLayout* dispLayout = new QVBoxLayout;
  QLayout* chatLayout = new QVBoxLayout;
  QLayout* chatbar = new QHBoxLayout;
  QPushButton* send = new QPushButton("Send");
  QObject::connect(send, SIGNAL(clicked()), this, SLOT(sendChatMsg()));
  send->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  console = new QTextEdit;
  chatwind = new QTextEdit;
  chat = new QLineEdit;
  chatbar->addWidget(chat);
  chatbar->addWidget(send);
  chatwind->setReadOnly(true);
  console->setReadOnly(true);
  chatLayout->addWidget(chatwind);
  chatLayout->addItem(chatbar);
  dispLayout->addItem(chatLayout);
  dispLayout->addWidget(console);
  gameScreen->addItem(dispLayout);
  gameLayout = new QWidget;
  gameLayout->setLayout(mainLayout);
}

void GUI::closeEvent(QCloseEvent* cE) {
  guiClient->send_message("SORT/"+username+"/\n");
  guiClient->terminate();
}

void GUI::sendChatMsg() {
  std::string msg = chat->text().toStdString();
  if (msg.compare("") != 0) {
    std::string command = "MESSAGE/"+username+"/"+msg+"/\n";
    guiClient->send_message(command);
    recvMsg("You", msg);
    chat->clear();
  }
}

void GUI::encherir() {
  int ench = QInputDialog::getInt(this, trUtf8("Enchère"), trUtf8("Enchère à envoyer"));
  guiClient->send_message("ENCHERE/"+username+"/"+std::to_string(ench)+"/\n");
}

void GUI::trouve() {
  int coups = QInputDialog::getInt(this, trUtf8("Solution"), 
				  trUtf8("Nombre de coups trouvé"));
  std::string comm = SOLCOMM_REF;
  guiClient->send_message(comm+"/"+username+"/"+std::to_string(coups)+"/\n");
}

void GUI::clientSendMoves(std::string moves) {
  guiClient->send_message("SOLUTION/"+username+"/"+moves+"/\n");
}

GUI::~GUI()
{
  delete ui;
}

/****************************************************/
/*             GUI QTHREAD INTERACTION              */
/****************************************************/

/** General messages **/

void GUI::gui_handleUnknownMessage(std::string msg) {
  ui_debug("handling unknownmsg");
  consoleMsg(msg);
}

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
}

void GUI::gui_handleSessionMsg(std::vector<std::string> args) {
  std::string game = args[0];
  std::vector<std::string> walls = split(game, ')');
  walls.pop_back(); // Remove the trailing empty string
  ui_debug("handling sessionmsg");
  plateau->resetRepr();
  for (std::string wall : walls) {
    wall = wall.substr(1, std::string::npos);
    std::vector<std::string> coords = split(wall, ',');
    // Hard-coded for x, y, dir
    int x = stoi(coords[0]), y = stoi(coords[1]);
    direction d = stodir((char)coords[2][0]);
    plateau->getRepr()->addWall(x, y, d);
  }
  plateau->repaint();
  consoleMsg("Server provided new game board.");
}

std::vector<coord> parsePuzzle(std::vector<std::string> puzzle) {
  std::vector<coord> res;
  // Hardcoded for 5 groups of coords
  for (size_t i = 0; i < 10; i+=2) {
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
  // Hard-coded for single target trailing the robot pos
  for (size_t i = 0; i < pos.size() - 1; i++) {
    plateau->getRepr()->setRobot((color) i, pos[i]);
    plateau->setRobot((color) i, pos[i]);
  }
  plateau->setRobotsOrigin();
  plateau->getRepr()->setRobotCible(stocol(puzzle[puzzle.length()-1]));
  plateau->getRepr()->setCible(pos[pos.size() - 1]);
  plateau->update();
  
  // Dpkg the score recap for current players
  std::string tmp = "";
  while (bilan[0] != '(') {
    tmp += bilan[0];
    bilan = bilan.substr(1, std::string::npos);
  }
  int tour = stoi(tmp);
  // Bilan assumed correctly formatted
  bilan = bilan.substr(1, bilan.length() - 2);
  bilan = remove(bilan, ')');
  std::vector<std::string> newscores = split(bilan, '(');
  for (std::string vect : newscores) {
    std::vector<std::string> nv = split(vect, ',');
    this->scores[nv[0]] = stoi(nv[1]);
  }
  consoleMsg("Server provided new turn description.");
  std::string scoremsg = "\nScores at turn "+std::to_string(tour)+": \n";
  for (const auto& kv : scores)
    scoremsg += kv.first + ": " + std::to_string(kv.second) + "\n";
  consoleMsg(scoremsg);
}

void GUI::gui_handleWinnerMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling winnermsg");
  consoleMsg("Winner: "+user);
}

/** Thinking Phase Messages **/

void GUI::gui_handleUFoundMsg(std::vector<std::string> args) {
  ui_debug("handling ufoundmsg");
  enchB->setEnabled(true);
  consoleMsg("Your solution was confirmed!");
}

void GUI::gui_handleHeFoundMsg(std::vector<std::string> args) {
  std::string user = args[0];
  int coups = stoi(args[1]);
  ui_debug("handling hefoundmsg");
  enchB->setEnabled(true);
  consoleMsg("User "+user+" found a solution in "+std::to_string(coups)+"moves.");
}

void GUI::gui_handleEndThinkMsg(std::vector<std::string> args) {
  ui_debug("handling endthinkmsg");
  enchB->setEnabled(true);
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

void GUI::gui_handleValidBid(std::vector<std::string> args) {
  ui_debug("handling validbidmsg");
  consoleMsg("Your bid was accepted.");
}

void GUI::gui_handleFailBidMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling failbidmsg");
  consoleMsg("Your bid failed: conflicts with user"+user+"'s.");
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
  // Reset robots
  plateau->reset();
  // Play out the solution
  for (size_t i = 0; i < dvect.size(); i++) {
    coldir cd = dvect[i];
    plateau->moveRobot(cd.col, cd.dir);
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
  if (user.compare(this->username) == 0)
    consoleMsg("Your solution was rejected. Your turn.");
  else
    consoleMsg("Solution rejected. Next user: " + user);
}

void GUI::gui_handleEndSolveMsg(std::vector<std::string> args) {
  ui_debug("handling endsolvemsg");
  consoleMsg("End of solution phase");
}

void GUI::gui_handleTimeoutMsg(std::vector<std::string> args) {
  std::string user = args[0];
  ui_debug("handling timeoutmsg");
  if (user.compare(this->username) == 0)
    consoleMsg("Your turn to offer a solution");
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

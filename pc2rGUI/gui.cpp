#include "gui.h"
#include "ui_gui.h"

#define NB_CASES 16
#define WALL_W 5

GUI::GUI(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::GUI)
{
  ui->setupUi(this);
}

GUI::~GUI()
{
  delete ui;
}

/**
 * Widget Plateau:
 * Représente le jeu (communique avec la repr du client)
 * Maintient une liste des mouvements du joueur
 */

PlateauWidget::PlateauWidget(QWidget* parent)://, session* maSession) :
  QFrame(parent), 
  guiRepr(new repr()),
  moveList(new std::list<coldir>())
  //  guiSession(maSession)
{
  setFrameStyle(QFrame::Panel | QFrame::Raised);
  setAutoFillBackground(true);
  // Init robots
  std::vector<Robot*> robots;
  for (int i = 0; i < 4; i++) {
    coord xy = guiRepr->getRobots()[i];
    robots.push_back(new Robot(this, guiRepr, color(i), xy.x, xy.y));
  }
}

void PlateauWidget::paintEvent(QPaintEvent *pe) {
  QFrame::paintEvent(pe);

  /**
   * Paint the grid
   */
  int h = std::min(size().height(), size().width()); // Always a square
  int cSize = h / NB_CASES;
  QPainter * painter = new QPainter(this);
  QPen * pen = new QPen;
  pen->setWidth(1);
  painter->setPen(*pen);
  painter->setBrush(Qt::black);
  for (int i = 0; i <= NB_CASES; i++) {
    painter->drawLine(i*cSize, 0, i*cSize, NB_CASES*cSize); // Vertical
    painter->drawLine(0, i*cSize, NB_CASES*cSize, i*cSize); // Horizontal
  }
  guiRepr->addWall(2, 2, stodir('B')); // Testing
  /* Paint the grid walls */
  paintWalls(guiRepr->getMurs(), painter);
  /* Paint the target*/
  coord target = guiRepr->getCible();
  QRect trect (target.x*cSize+1, target.y*cSize+1, cSize-1, cSize-1);
  painter->fillRect(trect, QBrush(QColor("purple")));
  painter->end();
}

void PlateauWidget::paintWalls(std::vector<direction>** murs, QPainter* p) {
  QPen* pen = new QPen;
  pen->setWidth(WALL_W);
  p->setPen(*pen);
  p->setBrush(Qt::darkYellow);
  for (int i = 0; i < NB_CASES; i++) {
    for (int j = 0; j < NB_CASES; j++) {
      if (murs[i][j].empty()) 
        continue;
      else {
	for (direction d : murs[i][j]) {
	  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	  switch (d) {
	  case Haut:
	    x1 = i*cSize + WALL_W/2;
	    y1 = j*cSize;
	    x2 = (i+1)*cSize - WALL_W/2;
	    y2 = j*cSize;
	    break;
	  case Bas:
	    x1 = i*cSize + WALL_W/2;
	    y1 = (j+1)*cSize;
	    x2 = (i+1)*cSize - WALL_W/2;
	    y2 = (j+1)*cSize;
	    break;
	  case Gauche:
	    x1 = i*cSize;
	    y1 = j*cSize + WALL_W/2;
	    x2 = i*cSize;
	    y2 = (j+1)*cSize - WALL_W/2;
	    break;
	  case Droite:
	    x1 = (i+1)*cSize;
	    y1 = j*cSize + WALL_W/2;
	    x2 = (i+1)*cSize;
	    y2 = (j+1)*cSize - WALL_W/2;
	    break;
	  }
	  p->drawLine(x1, y1, x2, y2);
	}
      }
    }
  }
}


void PlateauWidget::resizeEvent(QResizeEvent *qre) {
  cSize = std::min(size().height(), size().width()) / NB_CASES;
  update();
}

void PlateauWidget::undo() {
  coldir cd = moveList->front();
  if (!(moveList->empty()))
    moveList->pop_front();
}

void PlateauWidget::reset() {
  while (!(moveList->empty()))
    moveList->pop_front();
}

void PlateauWidget::addMove(color c, direction d) {
  moveList->push_front({c, d});
}

/**
 * QPushButton Robot: représente un robot dans le jeu
 * Permet de track les positions et les mouvements
 */

Robot::Robot(QWidget* parent, repr* rep, color col, int x, int y) : 
  QWidget(parent),
  guiRepr(rep),
  c(col),
  posX(x),
  posY(y)
{
  int pSize = std::min(parentWidget()->size().width(), 
		  parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  setGeometry(getX()*cSize, getY()*cSize, cSize, cSize);  
}

QPixmap scPm(char* path, int h, int w) {
  QPixmap pm(path);
  QPixmap sc = pm.scaled(h, w);
  return sc;
}

void Robot::paintEvent(QPaintEvent* qpe) {
  int pSize = std::min(parentWidget()->size().width(), 
		  parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  QPainter * painter = new QPainter(this);
  QPen * pen = new QPen;
  pen->setWidth(1);
  painter->setPen(*pen);
  QRect center(cSize/3, cSize/3, cSize/3, cSize/3);
  // For mouseclick checks
  north = new QRect(cSize/3, 0, cSize/3, cSize/3);
  south = new QRect(cSize/3, 2*cSize/3, cSize/3, cSize/3);
  west = new QRect(0, cSize/3, cSize/3, cSize/3);
  east = new QRect(2*cSize/3, cSize/3, cSize/3, cSize/3);
  // Robot colors
  switch (c) {
  case Rouge:
    painter->drawPixmap(0, 0, scPm("../assets/r_rouge", cSize, cSize));
    break;
  case Jaune:
    painter->drawPixmap(0, 0, scPm("../assets/r_jaune", cSize, cSize));
    break;
  case Bleu:
    painter->drawPixmap(0, 0, scPm("../assets/r_bleu", cSize, cSize));
    break;
  case Vert:
    painter->drawPixmap(0, 0, scPm("../assets/r_vert", cSize, cSize));
    break;
  }painter->end();
  // Position update
  setGeometry(getX()*cSize, getY()*cSize, cSize, cSize);
}

void Robot::mousePressEvent(QMouseEvent* qme) {
  std::cout << "clicked!" << std::endl;
  if (north->contains(qme->x(), qme->y()))
    receiveDir(direction::Haut);
  if (south->contains(qme->x(), qme->y()))
    receiveDir(direction::Bas);
  if (west->contains(qme->x(), qme->y()))
    receiveDir(direction::Gauche);
  if (east->contains(qme->x(), qme->y()))
    receiveDir(direction::Droite);
}

void Robot::receiveDir(direction d) {
  int pSize = std::min(parentWidget()->size().width(), 
		       parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  coord xy = guiRepr->moveRobot(c, d);
  std::cout << "Mvt to:" << xy.x << "," << xy.y << std::endl;
  setX(xy.x);
  setY(xy.y);
  guiRepr->setRobot(c, xy);
  move(getX()*cSize, getY()*cSize);
  std::cout << "New pos:" << pos().x() << "," << pos().y() << std::endl;
  emit(SIGNAL(robotMoved(c, d)));
  update();
}

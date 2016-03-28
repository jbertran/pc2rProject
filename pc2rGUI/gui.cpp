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
  guiRepr(new repr())
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
  for (Robot* r : robots) 
    r->move(r->getX(), r->getY());
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
  switch (col) {
  case Rouge:
    affC = Qt::red;
    break;
  case Jaune:
    affC = Qt::yellow;
    break;
  case Vert:
    affC = Qt::green;
    break;
  case Bleu:
    affC = Qt::blue;
    break;
  }  
}

void Robot::paintEvent(QPaintEvent* qpe) {
  int pSize = std::min(parentWidget()->size().width(), 
		  parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  QPainter * painter = new QPainter(this);
  QPen * pen = new QPen;
  pen->setWidth(1);
  painter->setPen(*pen);
  painter->setBrush(affC);
  QRect center(cSize/3, cSize/3, cSize/3, cSize/3);
  north = new QRect(cSize/3, 0, cSize/3, cSize/3);
  south = new QRect(cSize/3, 2*cSize/3, cSize/3, cSize/3);
  west = new QRect(0, cSize/3, cSize/3, cSize/3);
  east = new QRect(2*cSize/3, cSize/3, cSize/3, cSize/3);
  // Do this with static images
  // QRects only here for mouseclick check
  // Center ellipse
  painter->drawEllipse(center);
  // Arrow triangles
  // North
  QPainterPath path;
  path.moveTo(north->left() + (north->width()/2), north->top());
  path.lineTo(north->bottomLeft());
  path.lineTo(north->bottomRight());
  path.lineTo(north->left() + (north->width()/2), north->top());
  // South
  path.moveTo(south->left() + (south->width()/2), south->bottom());
  path.lineTo(south->topLeft());
  path.lineTo(south->topRight());
  path.lineTo(south->left() + (south->width()/2), south->bottom());
  // East
  path.moveTo(east->top() + (east->height()/2), east->right());
  path.lineTo(east->topLeft());
  path.lineTo(east->bottomLeft());
  path.lineTo(east->top() + (east->height()/2), east->right());
  // West
  path.moveTo(west->top() + (west->height()/2), west->left());
  path.lineTo(west->topRight());
  path.lineTo(west->bottomRight());
  path.lineTo(west->top() + (west->height()/2), west->left());
  painter->fillPath(path, QBrush(affC));
  // Position update
  move(getX()*cSize, getY()*cSize);
  painter->end();
}

void Robot::mousePressEvent(QMouseEvent* qme) {
  if (north.contains(qme->x, qme->y))
    receiveDir(Haut);
  if (south.contains(qme->x, qme->y))
    receiveDir(Bas);
  if (west.contains(qme->x, qme->y))
    receiveDir(Gauche);
  if (east.contains(qme->x, qme->y))
    receiveDir(Droite);
}

void Robot::resizeEvent(QResizeEvent* qre) {
  int pSize = std::min(parentWidget()->size().width(), 
		       parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  //resize(cSize, cSize);
  update();
}

void Robot::receiveDir(direction d) {
  coord xy = guiRepr->moveRobot(c, d);
  setX(xy.x);
  setY(xy.y);
  //move(getX()*sqSize + sqSize/2, getY()*sqSize + - sqSize/2) ;
}

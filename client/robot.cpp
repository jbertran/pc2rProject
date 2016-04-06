#include "robot.h"
#include "plateauWidget.h"
#include "repr.h"
#include "tools.h"


/**
 * QWidget Robot: représente un robot dans le jeu
 * Permet de track les positions et les mouvements
 */

Robot::Robot(QWidget* parent, repr* rep, color col, int x, int y) : 
  QWidget(parent),
  guiRepr(rep),
  c(col),
  posX(x),
  posY(y),
  origin({x, y})
{
  int pSize = std::min(parentWidget()->size().width(), 
		       parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  setGeometry(getX()*cSize, getY()*cSize, cSize, cSize);  
}

QPixmap scPm(const char* path, int h, int w) {
  QPixmap pm(path);
  QPixmap sc = pm.scaled(h, w);
  return sc;
}

void Robot::reset(color col) {
  if (col == c) {
    int pSize = std::min(parentWidget()->size().width(), 
			 parentWidget()->size().height());
    int cSize = pSize/NB_CASES;
    setX(origin.x);
    setY(origin.y);
    guiRepr->setRobot(c, origin);
    setGeometry(getX()*cSize, getY()*cSize, cSize, cSize);  
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

void Robot::receiveDir(direction d) {
  int pSize = std::min(parentWidget()->size().width(), 
		       parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  coord prev = {getX(), getY()};
  coord xy = guiRepr->moveRobot(c, d);
  setX(xy.x);
  setY(xy.y);
  guiRepr->setRobot(c, xy);
  setGeometry(getX()*cSize, getY()*cSize, cSize, cSize);
  s_move m;
  m.col = c;
  m.dir = d;
  m.depart = prev;
  emit robotMoved(m);
  update();
}

void Robot::mousePressEvent(QMouseEvent* qme) {
  if (north->contains(qme->x(), qme->y()))
    receiveDir(direction::Haut);
  if (south->contains(qme->x(), qme->y()))
    receiveDir(direction::Bas);
  if (west->contains(qme->x(), qme->y()))
    receiveDir(direction::Gauche);
  if (east->contains(qme->x(), qme->y()))
    receiveDir(direction::Droite);
}

void Robot::moveRobot(color col, coord xy) {
  int pSize = std::min(parentWidget()->size().width(), 
		       parentWidget()->size().height());
  int cSize = pSize/NB_CASES;
  if (col == c) {
    setX(xy.x);
    setY(xy.y);
    guiRepr->setRobot(c, xy);
    setGeometry(getX()*cSize, getY()*cSize, cSize, cSize);
  }
}

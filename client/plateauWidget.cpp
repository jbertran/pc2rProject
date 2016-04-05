#include "plateauWidget.h"

/**
 * Widget Plateau:
 * Représente le jeu (communique avec la repr du client)
 * Maintient une liste des mouvements du joueur
 */

PlateauWidget::PlateauWidget(QWidget* parent)://, session* maSession) :
  QFrame(parent), 
  guiRepr(new repr()),
  moveList(new std::list<s_move>())
{
  setFrameStyle(QFrame::Panel | QFrame::Raised);
  setAutoFillBackground(true);
  // Init robots
  std::vector<Robot*> robots;
  for (int i = 0; i < 4; i++) {
    coord xy = guiRepr->getRobots()[i];
    robots.push_back(new Robot(this, guiRepr, color(i), xy.x, xy.y));
  }
  for (Robot* r : robots) {
    QObject::connect(this, SIGNAL(resetRobot(color)),
		     r, SLOT(reset(color)));
    QObject::connect(this, SIGNAL(undoMove(color, coord)),
		     r, SLOT(moveRobot(color, coord)));
    QObject::connect(r, SIGNAL(robotMoved(s_move)),
		     this, SLOT(addMove(s_move)));
  }
}


void PlateauWidget::paintEvent(QPaintEvent *pe) {
  QFrame::paintEvent(pe);
  /* Paint the grid  */
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
  paintTarget(guiRepr->getRobotCible(), guiRepr->getCible(), cSize, painter);
  painter->end();
}

void PlateauWidget::paintTarget(color c, coord xy, int csize, QPainter* p) {
  QColor col;
  switch(c) {
  case color::Rouge:
    col = QColor("darkRed");
    break;
  case color::Jaune:
    col = QColor("darkYellow");
    break;
  case color::Vert:
    col = QColor("darkGreen");
    break;
  case color::Bleu:
    col = QColor("darkBlue");
    break;
  }
  QRect trect (xy.x*cSize+1, xy.y*cSize+1, cSize-1, cSize-1);
  p->fillRect(trect, QBrush(col));
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
 *   Plateau SLOTS
 */

void PlateauWidget::undo() {
  if (!(moveList->empty())){
    s_move m = moveList->front();
    int occs = 0;
    std::list<s_move> tmpl(*moveList);
    while (!(tmpl.empty())) {
      s_move tmp = tmpl.front();
      if (tmp.col == m.col)
	occs++;
      if (occs >= 2)
	break;
    }
    if (occs < 2)
      emit resetRobot(m.col);
    else
      emit undoMove(m.col, m.depart);
    emit counterDecr();
    moveList->pop_front();
  }
}

void PlateauWidget::reset() {
  while (!(moveList->empty()))
    moveList->pop_front();
  emit resetRobot(color::Rouge);
  emit resetRobot(color::Jaune);
  emit resetRobot(color::Vert);
  emit resetRobot(color::Bleu);
  emit counterReset();
}

void PlateauWidget::valider() {
  coord robot = guiRepr->getRobot(guiRepr->getRobotCible());
  coord cible = guiRepr->getCible();
  if(cible.x == robot.x && cible.y == robot.y) {
    std::cout << "jdsioqjdqs" << std::endl;
  }
}

void PlateauWidget::addMove(s_move m) {
  moveList->push_front(m);
  emit counterIncr();
}

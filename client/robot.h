#ifndef __robot__
#define __robot__

#include <iostream>
#include <cstdlib>
#include <QWidget>
#include <QRect>
#include <QMouseEvent>
#include <QPainter>
#include "repr.h"
#include "tools.h"

/**
 * Le widget de tracking des positions de robots
 * et d'interaction avec les robots
 */
class Robot : public QWidget
{

  Q_OBJECT

public:
  explicit Robot(QWidget* parent = 0, repr* rep = 0,
		 color c = Rouge, int x = 0, int y = 0);
  color getColor() { return c; }
  int getX() { return posX; };
  int getY() { return posY; };
  void setX(int x) { posX = x; };
  void setY(int y) { posY = y; };
  void receiveDir(direction d);
  void reset();
public slots:
  void moveRobot(color c, coord xy);
  void reset(color c);
signals:
  void robotMoved(s_move m);
protected:
  void paintEvent(QPaintEvent* qpe);
  void mousePressEvent(QMouseEvent* qme);
private:
  QRect* north;
  QRect* south;
  QRect* east; 
  QRect* west;
  repr* guiRepr;
  color c;
  int posX, posY;
  coord origin;
};

#endif

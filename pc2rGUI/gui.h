#ifndef GUI_H
#define GUI_H

#include <string>
#include "../client/repr.h"
#include "../client/tools.h"
#include <QMainWindow>
#include <QLine>
#include <QFrame>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QGridLayout>
#include <QBrush>
#include <QColor>
#include <QRect>
#include <QPen>
#include <iostream>

namespace Ui {
class GUI;
}

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUI(QWidget *parent = 0);
    ~GUI();

private:
    Ui::GUI *ui;
};

/**
 * PlateauWidget: le Widget sur lequel on peint les 
 *          cases, et sur lequel on place les robots.
 * Méthode draw importante.
 */
class Robot;

class PlateauWidget : public QFrame
{

  Q_OBJECT

public:
  explicit PlateauWidget(QWidget* parent = 0);//, session* maSession = 0);
  int getCSize() { return cSize; }
protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent*);
public slots:
  void reset();
  void undo();
  void valider();
  void addMove(s_move m);
signals:
  void resetRobot(color c);
  void undoMove(color c, coord xy);
private:
  int cSize;
  void paintWalls(std::vector<direction>** murs, QPainter* p);
  repr* guiRepr;
  std::list<s_move>* moveList;
  // session* guiSession;
};


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

#endif // GUI_H

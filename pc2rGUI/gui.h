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
  void addMove(color c, direction d);
private:
  int cSize;
  void paintWalls(std::vector<direction>** murs, QPainter* p);
  repr* guiRepr;
  // TODO
  Robot* robots;
  std::vector<coldir>* moveList;
//  session* guiSession;
};


/**
 * Le widget de tracking des positions de robots
 * et d'interaction avec les robots
 */
class Robot : public QWidget
{

  Q_OBJECT

public:
  explicit Robot(QWidget* parent = 0, repr* rep = 0, color c = Rouge, int x = 0, int y = 0);
  color getColor() { return c; }
  int getX() { return posX; };
  int getY() { return posY; };
  void setX(int x) { posX = x; };
  void setY(int y) { posY = y; };
public slots:
  void receiveDir(direction d);
signals:
  void doMove(color c, direction d);
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
  QColor affC;
  int posX, posY;
};

#endif // GUI_H

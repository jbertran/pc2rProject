#include <iostream>
#include <cstdlib>
#include <QFrame>
#include <QPainter>

#include "tools.h"
#include "repr.h"
#include "robot.h"

#define NB_CASES 16
#define WALL_W 5

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
  void counterIncr();
  void counterDecr();
  void counterReset();
  void resetRobot(color c);
  void undoMove(color c, coord xy);
private:
  int cSize;
  void paintWalls(std::vector<direction>** murs, QPainter* p);
  void paintTarget(color c, coord xy, int cSize, QPainter* p);
  repr* guiRepr;
  std::list<s_move>* moveList;
};

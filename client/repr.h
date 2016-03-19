#ifndef __repr__
#define __repr__

#include <vector>

#define PLAT_SIZE 16

enum color     { Rouge, Jaune, Vert, Bleu  };
enum direction { Haut, Bas, Droite, Gauche };

typedef struct _coord {
  int x;
  int y;
} coord;

typedef struct _coldir {
  color col;
  direction dir;
} coldir;

/** ColDir helpers **/
color stocol(char s);
direction stodir(char s);

class repr {

  int height, width;
  color robot_cible;
  coord cible;
  coord robots [4];
  std::vector<direction>** murs;

public:
  /** Constructor **/
  repr();
  
  /** Initializer **/
  void initialize();

  /**   Getters  **/
  coord getCible()   { return cible;  }
  int getHeight()    { return height; }
  int getWidth()     { return width;  }
  coord* getRobots() { return robots; }
  std::vector<direction>** getMurs()  { return murs; }
  bool hasWall(int x, int y, direction d);
  bool hasRobot(int x, int y);
  coord getRobot(color c);

  /** Operations **/
  void setRobot(color c, coord co);
  void setCible(coord co);
  void addWall(int x, int y, direction d);
  coord moveRobot(color c, direction d);
  repr clone();
  bool is_valid(std::vector<coldir>);
};

#endif

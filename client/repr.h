#ifndef __repr__
#define __repr__

#include <vector>

enum color     { Rouge, Jaune, Vert, Bleu  };
enum class direction { Haut, Bas, Droite, Gauche };

typedef struct _coord {
  int x;
  int y;
} coord;

typedef struct _coldir {
  color col;
  direction dir;
} coldir;

class repr {

  int height, width;
  color robot_cible;
  coord cible;
  std::vector<coord> robots;
  std::vector<std::vector<std::vector<direction>>> murs;

 public:
  /** Constructor **/
  repr(int h, int w) { height = h; width = w; } 
  
  /** Initializer **/
  void initialize();

  /**   Getters  **/
  coord getCible()   { return cible;  }
  int getHeight()    { return height; }
  int getWidth()     { return width;  }
  std::vector<coord> getRobots() { return robots; }
  std::vector<std::vector<std::vector<direction>>> getMurs()  { return murs; }
  bool hasWall(int x, int y, direction d);
  bool hasRobot(int x, int y);
  coord getRobot(color c);

  /** Operations **/
  void addWall(int x, int y, direction d);
  coord moveRobot(color c, direction d);
  repr clone();
  bool is_valid(std::vector<coldir>);
};

#endif

#ifndef __gamestate__
#define __gamestate__

enum class color     { Rouge, Vert, Jaune, Bleu  };
enum class direction { Haut, Bas, Droite, Gauche };

class coord {
  int x, y;
 public:
 coord(int xc, int yc) :x{xc}, y{yc} {}
  int getX() { return x; }
  int getY() { return y; }
}

class gameState {

  int height, width;
  color robot_cible;
  coord cible;
  coord robots [];
  coord murs [][];

 public:
  /** Constructeurs **/
  gameState(int x, int y);
  
  /** Initializer **/
  init();

  /**   Accesseurs  **/
  coord cible()   { return cible;  }
  coord* robots() { return robots; }
  coord** murs()  { return murs;   }
  int height()    { return height; }
  int width()     { return width;  }

}

#endif

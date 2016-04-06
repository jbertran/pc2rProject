#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "repr.h"

// #define RP_DEBUG 1

#ifdef RP_DEBUG
#define rp_debug(str) { std::cout << str << std::endl; }
#else
#define rp_debug(str) ;
#endif

using namespace std;

repr::repr() {
  rp_debug("new repr");
  vector<direction>** murs = new vector<direction>* [PLAT_SIZE];
  for (int i = 0; i < PLAT_SIZE; i++) {
    murs[i] = new vector<direction> [PLAT_SIZE];
    for (int j = 0; j < PLAT_SIZE; j++)
      (murs[i])[j] = vector<direction>();
  }
  this->murs = murs;
  /** Murs externes - mis par sécurité **/
  for (int i = 0; i < PLAT_SIZE; i++) {
    addWall(0, i, direction::Gauche);
    addWall(PLAT_SIZE-1, i, direction::Droite);
    addWall(i, 0, direction::Haut);
    addWall(i, PLAT_SIZE-1, direction::Bas);
  }
  for (int i = 0; i < 4; i++)
    robots[i] = { i*2, i*2 };
  robot_cible = color::Rouge;
  cible={0,0};
}

bool repr::hasWall(int x, int y, direction d) {
  rp_debug("haswall");
  if (((x < 0) && (d == direction::Gauche)) ||
      ((x >= PLAT_SIZE) && (d == direction::Droite)) ||
      ((y < 0) && (d == direction::Haut)) ||
      ((y >= PLAT_SIZE) && (d == direction::Bas)))
    return true;
  for (direction md : murs[x][y])
    if (md == d)
      return true;
  return false;
}

bool repr::hasRobot(int x, int y) {
  rp_debug("hasrobot");
  for (int i = 0; i < 4; i++) {
    if (robots[i].x == x && robots[i].y == y)
      return true;
  }
  return false;
}

void repr::addWall(int x, int y, direction d) {
  rp_debug("addwall");
  murs[x][y].push_back(d);
  std::cout << murs[x][y].size() << std::endl;
}

coord repr::getRobot(color c) {
  return robots[c];
}

void repr::setRobot(color c, coord co) {
  rp_debug("setRobot");
  std::cout << co.x << "," << co.y << std::endl;
  this->robots[(int)c] = co;
}

void repr::setCible(coord c) {
  rp_debug("set target xy");
  this->cible = c;
}

void repr::setRobotCible(color c) {
  rp_debug("set target color");
  this->robot_cible = c;
}

coord repr::moveRobot(color c, direction d) {
  rp_debug("move robot");
  coord r = getRobot(c);
  int x = r.x, y = r.y;
  switch (d) {
  case direction::Haut:
    while (! ((y < 0) ||
	      (hasWall(x, y, direction::Haut)) ||
	      (hasWall(x, y-1, direction::Bas)) ||
	      (hasRobot(x, y-1))))
      y -= 1;
    break;
  case direction::Bas:
    while (! ((y >= PLAT_SIZE) ||
	      (hasWall(x, y, direction::Bas)) ||
	      (hasWall(x, y+1, direction::Haut)) ||
	      (hasRobot(x, y+1))))
      y += 1;
    break;
  case direction::Gauche:
    while (! ((x < 0) ||
	      (hasWall(x, y, direction::Gauche)) ||
	      (hasWall(x-1, y, direction::Droite)) ||
	      (hasRobot(x-1, y))))
      x -= 1;
    break;
  case direction::Droite:
    while (! ((x >= PLAT_SIZE) ||
	      (hasWall(x, y, direction::Droite)) ||
	      (hasWall(x+1, y, direction::Gauche)) ||
	      (hasRobot(x+1, y))))
      x += 1;
    break;
  default:
    cerr << "Invalid direction passed to moveRobot" << endl;
  }
  r.x = x;
  r.y = y;
  return r;
}

bool repr::is_valid(vector<coldir> movelist) {
  rp_debug("check validity");
  vector<coord> tmprobots;
  for (int i = 0; i < 4; i++)
    tmprobots.push_back(robots[i]);
  for (coldir cd : movelist) {
    color c = cd.col;
    direction d = cd.dir;
    coord mv = moveRobot(c, d);
    tmprobots[c] = mv;
  }
  return (tmprobots[robot_cible].x == cible.x && 
	  tmprobots[robot_cible].y == cible.y);
}

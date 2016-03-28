#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "repr.h"

using namespace std;

repr::repr() {
  vector<direction>** murs = new vector<direction>* [PLAT_SIZE];
  for (int i = 0; i < PLAT_SIZE; i++) {
    murs[i] = new vector<direction> [PLAT_SIZE];
    for (int j = 0; j < PLAT_SIZE; j++)
      (murs[i])[j] = vector<direction>();
  }
  this->murs = murs;
  // Murs externes
  for (int i = 0; i < PLAT_SIZE; i++) {
    addWall(0, i, direction::Gauche);
    addWall(PLAT_SIZE-1, i, direction::Droite);
    addWall(i, 0, direction::Haut);
    addWall(i, PLAT_SIZE-1, direction::Bas);
  }
  for (int i = 0; i < 4; i++)
    robots[i] = { i+1, i+1 };
}

bool repr::hasWall(int x, int y, direction d) {
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
  for (int i = 0; i < 4; i++) {
    if (robots[i].x == x && robots[i].y == y)
      return true;
  }
  return false;
}

void repr::addWall(int x, int y, direction d) {
  murs[x][y].push_back(d);
}

coord repr::getRobot(color c) {
  return robots[c];
}

void repr::setRobot(color c, coord co) {
  this->robots[(int)c] = co;
}

void repr::setCible(coord c) {
  this->cible = c;
}

coord repr::moveRobot(color c, direction d) {
  cout << "moveRobot" <<  endl;
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

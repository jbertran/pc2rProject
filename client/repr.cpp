#include <iostream>
#include <unordered_map>
#include <vector>
#include "repr.h"

using namespace std;

repr::repr() {
  vector<direction>** murs = new vector<direction>* [PLAT_SIZE];
  for (int i = 0; i < PLAT_SIZE; i++) {
    murs[i] = new vector<direction> [PLAT_SIZE];
    for (int j = 0; i < PLAT_SIZE; i++)
      (murs[i])[j] = vector<direction>();
  }
}

bool repr::hasWall(int x, int y, direction d) {
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
  for (direction md : murs[x][y])
    if (md == d)
      return;
    else
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
  coord r = getRobot(c);
  int x = r.x, y = r.y;
  switch (d) {
  case direction::Haut:
    while (! ((hasWall(x, y, direction::Haut)) ||
	      (hasWall(x-1, y, direction::Bas)) ||
	      (hasRobot(x, y))))
      x -= 1;
    break;
  case direction::Bas:
    while (! ((hasWall(x, y, direction::Bas)) ||
	      (hasWall(x+1, y, direction::Haut)) ||
	      (hasRobot(x, y))))
      x += 1;
    break;
  case direction::Gauche:
    while (! ((hasWall(x, y, direction::Gauche)) ||
	      (hasWall(x, y-1, direction::Droite)) ||
	      (hasRobot(x, y))))
      y -= 1;
    break;
  case direction::Droite:
    while (! ((hasWall(x, y, direction::Droite)) ||
	      (hasWall(x, y+1, direction::Gauche)) ||
	      (hasRobot(x, y))))
      y += 1;
    break;
  default:
    cerr << "Invalid color passed to moveRobot" << endl;
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

color stocol(char s) {
  unordered_map<char, color> stocol =
    {
      {'R', color::Rouge},
      {'J', color::Jaune},
      {'V', color::Vert},
      {'B', color::Bleu}
    };
  if (stocol.count(s) <= 0) {
    cerr << "Unknown color!" << endl;
    return stocol['R'];
  }
  else
    return stocol[s];
} 

direction stodi(char s) {
  unordered_map<char, direction> stodir = 
    {
      {'H', direction::Haut},
      {'B', direction::Bas},
      {'G', direction::Gauche},
      {'D', direction::Droite}
    };
  if (stodir.count(s) <= 0) {
    cerr << "Unknown direction!" << endl;
    return stodir['H'];
  }
  else
    return stodir[s];
}

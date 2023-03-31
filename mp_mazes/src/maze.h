#pragma once

#include <vector>
#include <queue>
#include <utility>
#include "dsets.h"
#include "../lib/cs225/PNG.h"

using namespace std;
using namespace cs225;

class SquareMaze
{
  public:
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void 	setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG *drawMaze() const;
  PNG *drawMazeWithSolution();

  private:
  vector<vector<pair<bool, bool>>> graph;
  DisjointSets dset;
  const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
  int width_, height_;
};
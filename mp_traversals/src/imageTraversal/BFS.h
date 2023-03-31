/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek();
  bool empty();
  const HSLAPixel &get(Point t);
  void addd(const Point & point);
  bool visited(Point t);
  PNG* getpng() { return &png_; };
// private:
  /** @todo [Part 1] */
  /** add private members here*/
  std::queue<Point> q;
  double tolerance_;
  PNG png_;
  std::vector<std::vector<bool>> st;
  Point start_;
  int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
};

#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  tolerance_ = tolerance;
  png_ = png;
  st = std::vector<std::vector<bool>>(png_.width(), std::vector<bool>(png_.height(), false));
  start_ = start;
  add(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(start_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator({UINT32_MAX, UINT32_MAX}, this);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  if (point.x < png_.width() && point.y < png_.height()) stk.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  while (!stk.empty() && visited(stk.top())) stk.pop();
  Point ret = stk.top(); 
  stk.pop();
  st[ret.x][ret.y] = true;
  return ret;
}

void DFS::addd(const Point & point) {
  /** @todo [Part 1] */
  for (unsigned d = 0; d < 4; ++ d)
  {
    unsigned x = point.x + dx[d], y = point.y + dy[d];
    if (x >= png_.width() || y >= png_.height() || st[x][y] || tolerance_ <= calculateDelta(get(start_), get({x, y}))) continue;
    add({x, y});
  }
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() {
  /** @todo [Part 1] */
  while (!stk.empty() && visited(stk.top())) stk.pop();
  if (empty()) return {UINT32_MAX, UINT32_MAX};
  return stk.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() {
  /** @todo [Part 1] */
  while (!stk.empty() && visited(stk.top())) stk.pop();
  return stk.empty();
}

const HSLAPixel &DFS::get(Point t)
{
  return png_.getPixel(t.x, t.y);
}

bool DFS::visited(Point t) {
  if (t.x >= png_.width() || t.y >= png_.height()) return true;
  return st[t.x][t.y];
}
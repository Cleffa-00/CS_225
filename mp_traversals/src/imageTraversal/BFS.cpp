#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(start_, this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator({UINT32_MAX, UINT32_MAX}, this);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if (point.x < png_.width() && point.y < png_.height()) {
    q.push(point);
    st[point.x][point.y] = true;
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point ret = peek(); 
  if (!empty()) q.pop();
  return ret;
}

void BFS::addd(const Point & point) {
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
Point BFS::peek() {
  /** @todo [Part 1] */
  if (empty()) return {UINT32_MAX, UINT32_MAX};
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() {
  /** @todo [Part 1] */
  return q.empty();
}

const HSLAPixel &BFS::get(Point t)
{
  return png_.getPixel(t.x, t.y);
}

bool BFS::visited(Point t) {
  if (t.x >= png_.width() || t.y >= png_.height()) return true;
  return st[t.x][t.y];
}
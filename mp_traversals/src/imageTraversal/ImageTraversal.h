/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"
#include <stack>

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    /** @todo [Part 1] */
    /** add member functions if neccesary*/
    Iterator(Point cur_, ImageTraversal *graph_) : cur(cur_), start(cur_), graph(graph_) {}
  // private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    Point cur;
    Point start;
    ImageTraversal * graph;
  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() = 0;
  virtual void addd(const Point & t) = 0;
  virtual bool visited(Point t) = 0;
  virtual PNG* getpng() = 0;
  // std::stack<Point> stk;
// private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
};

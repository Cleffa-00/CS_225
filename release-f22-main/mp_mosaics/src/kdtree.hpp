/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim]) return first < second;
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double cur = 0.0, rep = 0.0;
    for (int i = 0; i < Dim; ++ i) {
      cur += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      rep += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    return cur == rep ? potential < currentBest : cur > rep;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::build(int l, int r, int curDim) {
  if (l > r) return NULL;
  if (l == r) return new KDTree<Dim>::KDTreeNode(points[l]);
  size_t pivotIndex = partition(l, r, curDim);
  size_t mid = (l + r) >> 1;
  size_t t_left = l, t_right = r;
  while (pivotIndex != mid) {
    if (pivotIndex < mid)  {
      t_left = pivotIndex + 1; 
      pivotIndex = partition(t_left, t_right, curDim);
    }
    else {
      t_right = pivotIndex - 1;
      pivotIndex = partition(t_left, t_right, curDim);
    }
  }
  KDTree<Dim>::KDTreeNode* cur = new KDTree<Dim>::KDTreeNode(points[mid]);
  cur -> left = build(l, mid - 1, (curDim + 1) % Dim);
  cur -> right = build(mid + 1, r, (curDim + 1) % Dim);
  return cur;
}

template <int Dim>
size_t KDTree<Dim>::partition(size_t l, size_t r, int curDim) {
  if (l == r) return l;
  size_t i = rand() % (r - l + 1) + l;
  swap(points[i], points[r]);
  Point<Dim> x = points[r];
  i = l - 1;
  for (size_t j = l; j < r; ++ j) if (smallerDimVal(points[j], x, curDim)) swap(points[ ++ i], points[j]);
  swap(points[ ++ i], points[r]);
  return i;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    srand(time(0));
    points = newPoints;
    root = build(0, newPoints.size() - 1, 0);
    size = points.size();
    // printTree();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  if (other.root == NULL) root = NULL;
  else {
    root = new KDTree<Dim>::KDTreeNode(other.root -> point);
    copy(root, other.root);
  }
  size = other.size();
  points = other.points;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  deleteTree(root);
  size = rhs.size;
  points = rhs.points;
  if (rhs.root == NULL) root = NULL;
  else {
    root = new KDTree<Dim>::KDTreeNode(rhs.root -> point);
    copy(root, rhs.root);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  deleteTree(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
bool shouldReplace1(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential, int curDim)
{
    /**
     * @todo Implement this function!
     */
    double cur = 0.0, rep = 0.0;
    for (int i = 0; i < Dim; ++ i) {
      cur += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      if (i == curDim) rep += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    return cur >= rep;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* cur, int curDim) const {
  if (cur == nullptr) {
    double a[Dim];
    for (size_t i = 0; i < Dim; ++ i) a[i] = 2e9;
    return Point<Dim>(a);
  }
  Point<Dim> best, temp;
  if (smallerDimVal(query, cur -> point, curDim) && cur -> left != nullptr) {
    best = findNearestNeighbor(query, cur -> left, (curDim + 1) % Dim);
    if (shouldReplace1(query, best, cur -> point, curDim)) {
      temp = findNearestNeighbor(query, cur -> right, (curDim + 1) % Dim);
      if (shouldReplace(query, best, cur -> point)) best = cur -> point;
      if (shouldReplace(query, best, temp)) best = temp;
    }
  } else {
    best = findNearestNeighbor(query, cur -> right, (curDim + 1) % Dim);
    if (shouldReplace1(query, best, cur -> point, curDim)) {
      temp = findNearestNeighbor(query, cur -> left, (curDim + 1) % Dim);
      if (shouldReplace(query, best, cur -> point)) best = cur -> point;
      if (shouldReplace(query, best, temp)) best = temp;
    }
  }
  return best;
} 
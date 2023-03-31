/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List()
    : head_(nullptr), tail_(nullptr), length_(0)
{
  // @TODO: graded in MP3.1
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const
{
  // @TODO: graded in MP3.1
  if (tail_ != nullptr && tail_->next == nullptr)
  {
    ListNode *e = new ListNode();
    e->prev = tail_;
    tail_->next = e;
  }
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const
{
  // @TODO: graded in MP3.1
  if (tail_ != nullptr && tail_->next == nullptr)
  {
    ListNode *e = new ListNode();
    e->prev = tail_;
    tail_->next = e;
  }
  return tail_->next;
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy()
{
  ListNode *cur = head_;
  while (cur != nullptr)
  {
    ListNode *nex = cur->next;
    delete cur;
    cur = nex;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = nullptr;

  if (head_ != nullptr)
  {
    head_->prev = newNode;
  }
  if (tail_ == nullptr)
  {
    tail_ = newNode;
  }
  head_ = newNode;

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  newNode->prev = tail_;
  newNode->next = nullptr;

  if (tail_ != nullptr)
  {
    tail_->next = newNode;
  }
  if (head_ == nullptr)
  {
    head_ = newNode;
  }
  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode *List<T>::split(ListNode *start, int splitPoint)
{
  /// @todo Graded in MP3.1
  ListNode *curr = start;
  if (splitPoint == 0)
    return curr;

  for (int i = 0; i < splitPoint; i++)
  {
    curr = curr->next;
  }

  if (curr != nullptr)
  {
    curr->prev->next = nullptr;
    curr->prev = nullptr;
  }

  return curr;
}

/**
 * Modifies List using the rules for a TripleRotate.
 *
 * This function will to a wrapped rotation to the left on every three
 * elements in the list starting for the first three elements. If the
 * end of the list has a set of 1 or 2 elements, no rotation all be done
 * on the last 1 or 2 elements.
 *
 * You may NOT allocate ANY new ListNodes!
 */

template <typename T>
void List<T>::tripleRotate()
{
  ListNode *dummmy = new ListNode();
  dummmy->next = head_;
  head_->prev = dummmy;
  ListNode *pre = dummmy, *cur = head_, *temp = nullptr;
  while (cur != nullptr && cur->next != nullptr && cur->next->next != nullptr)
  {
    cur->next->prev = pre;
    pre->next = cur->next;
    cur->prev = cur->next->next;
    temp = cur->prev->next;
    cur->prev->next = cur;
    cur->next = nullptr;
    pre = cur;
    cur = temp;
  }
  if (cur != nullptr)
  {
    cur->prev = pre;
  }
  pre->next = cur;
  head_ = dummmy->next;

  delete dummmy;
  tail_ = head_;
  while (tail_ != nullptr && tail_->next != nullptr)
  {
    tail_ = tail_->next;
  }
  head_->prev = nullptr;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse()
{
  ListNode *left = head_, *right = tail_;
  reverse(left, right);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */

template <typename T>
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint)
{
  ListNode *first = startPoint->prev, *second = endPoint->next;
  ListNode *cur = startPoint, *pre = nullptr;
  while (cur != endPoint)
  {
    pre = cur->prev;
    cur->prev = cur->next;
    cur->next = pre;
    cur = cur->prev;
  }
  cur->next = cur->prev;
  if (first == nullptr)
    head_ = endPoint, head_->prev = nullptr;
  else
    first->next = endPoint, endPoint->prev = first;

  if (second == nullptr)
    tail_ = startPoint, tail_->next = nullptr;
  else
    second->prev = startPoint, startPoint->next = second;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  // if ()
  ListNode *left = head_, *right = nullptr;

  while (left != nullptr)
  {
    right = left;
    for (int i = 1; i < n && right != tail_; ++i)
      right = right->next;
    reverse(left, right);
    left = left->next;
  }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> &otherList)
{
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL)
  {
    while (tail_->next != NULL)
      tail_ = tail_->next;
  }
  head_->prev = nullptr;
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
  otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode *List<T>::merge(ListNode *first, ListNode *second)
{
  /// @todo Graded in MP3.2
  ListNode *dummy = new ListNode();
  ListNode *cur = dummy;

  while (first != nullptr && second != nullptr)
  {
    if (first->data < second->data)
    {
      cur->next = first;
      first->prev = cur;
      first = first->next;
      cur = cur->next;
    }
    else
    {
      cur->next = second;
      second->prev = cur;
      second = second->next;
      cur = cur->next;
    }
  }
  if (first != nullptr)
  {
    cur->next = first;
    first->prev = cur;
    first = first->next;
    cur = cur->next;
  }
  if (second != nullptr)
  {
    cur->next = second;
    second->prev = cur;
  }
  cur = dummy->next;
  delete dummy;
  return cur;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode *List<T>::mergesort(ListNode *start, int chainLength)
{
  if (chainLength == 0 || chainLength == 1)
    return start;
  return merge(mergesort(split(start, chainLength - chainLength / 2), chainLength / 2), mergesort(start, chainLength - chainLength / 2));
}
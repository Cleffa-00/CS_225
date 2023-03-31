/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}
template <typename T>
void BinaryTree<T>::mirror(Node* cur) {
    if (cur == nullptr) return;
    Node* temp = cur -> left;
    cur -> left = cur -> right;
    cur -> right = temp;
    mirror(cur -> left);
    mirror(cur -> right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    std::vector<Node *> v;
    std::stack<Node *> stk;
    Node* cur = root;
    while (cur != nullptr || stk.size()) {
        while (cur != nullptr) {
            stk.push(cur);
            cur = cur -> left;
        }
        cur = stk.top();
        stk.pop();
        v.push_back(cur);
        cur = cur -> right;
    }
    for (size_t i = 1; i < v.size(); ++ i) {
        if (v[i - 1] -> elem >= v[i] -> elem) return false;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* cur) const {
    if (cur == nullptr) return true;
    return isOrderedRecursive(cur -> left, cur -> elem, true) && isOrderedRecursive(cur -> right, cur -> elem, false) && isOrderedRecursive(cur -> left) && isOrderedRecursive(cur -> right);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* cur, T val, bool less) const {
    if (cur == nullptr) return true;
    return isOrderedRecursive(cur -> left, val, less) && isOrderedRecursive(cur -> right, val, less) && (cur -> elem < val == less);
}
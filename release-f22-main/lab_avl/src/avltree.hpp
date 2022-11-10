/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* y = t -> right;
    t -> right = y -> left;
    y -> left = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* y = t -> left;
    t -> left = y -> right;
    y -> right = t;
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t -> right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int balance = getHeight(subtree -> right) - getHeight(subtree -> left);
    if (balance == -2) {
        int l_balance = getHeight(subtree -> left -> right) - getHeight(subtree -> left -> left);
        if (l_balance == -1) rotateRight(subtree);
        else rotateLeftRight(subtree);
    } else if (balance == 2) {
        int r_balance = getHeight(subtree -> right -> right) - getHeight(subtree -> right -> left);
        if (r_balance == 1) rotateLeft(subtree);
        else rotateRightLeft(subtree);
    } else return;
    getHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr) { subtree = new Node(key, value); return; }
    if (key == subtree -> key) subtree -> value = value;
    else if (key < subtree -> key) insert(subtree -> left, key, value);
    else insert(subtree -> right, key, value);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::mySwap(Node*& x, Node*& y) 
{
    Node* t = x;
    x = y;
    y = t;
    t = x -> left;
    x -> left = y -> left;
    y -> left = t;
    t = x -> right;
    x -> right = y -> right;
    y -> right = t;
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* node) 
{
    if (node == nullptr) return -1;
    int x = getHeight(node -> left), y = getHeight(node -> right);
    node -> height = (x > y ? x : y) + 1;
    return node -> height;
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        remove(subtree -> right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = nullptr;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node* t = subtree -> left;
            Node** tt = &(subtree -> left);
            while (t -> right != nullptr) {
                tt = &(t -> right);
                t = t -> right;
            }
            if (t == subtree -> left) {
                Node* temp = subtree;
                t -> right = subtree -> right;
                subtree = t;
                delete temp;
            } else {
                mySwap(*tt, subtree);
                delete *tt;
                *tt = nullptr;
            }
        } else {
            Node* temp = subtree;
            subtree = subtree -> left == nullptr ? subtree -> right : subtree -> left;
            delete temp;
        }
        
    }
    rebalance(subtree);
}

/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    return find(root, key)->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == nullptr) return subtree;
    if (key < subtree->key) return find(subtree->left, key);
    else if (key == subtree->key) return subtree;
    else return find(subtree->right, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    Node*& node = find(root, key);
    if (node == nullptr) node = new Node(key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    Node* temp = first;
    first = second;
    second = temp;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    Node** x = &find(root, key);
    Node** y = x;
    if (*x == nullptr) return;
    if ((*x)->left == nullptr && (*x)->right == nullptr) {
        delete *x;
        *x = nullptr;
        return;
    } else if((*x)->right == nullptr || ((*x)->left != nullptr && (*x)->left->right == nullptr)) {
        Node* temp = *x;
        *x = (*x)->left;
        (*x)->right = temp->right;
        delete temp;
        return;
    } else if ((*x)->left == nullptr || ((*x)->right != nullptr && (*x)->right->left == nullptr)) {
        Node* temp = *x;
        *x = temp->right;
        (*x)->left = temp->left;
        delete temp;
        return;
    } else if ((*x)->left != nullptr) {
        y = &((*x)->left);
        while ((*y)->right != nullptr) y = &((*y)->right);
    } else {
        y = &((*x)->right);
        while ((*y)->left != nullptr) y = &((*y)->left);
    }
    swap(*x, *y);
    swap((*x)->right, (*y)->right);
    swap((*x)->left, (*y)->left);
    delete *y;
    *y = nullptr;

}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> ret = BST<K, V>();
    for (auto& i : inList) {
        ret.insert(i.first, i.second);
    }
    return ret;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> v = std::vector<int>(inList.size(), 0);
    std::sort(inList.begin(), inList.end());
    do {
        BST<K, V> temp = listBuild(inList);
        v[temp.height()] ++ ;
    } while (std::next_permutation(inList.begin(), inList.end()));
    return v;
}
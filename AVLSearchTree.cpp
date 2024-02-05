#include "AVLSearchTree.h"
#include <iostream>
using namespace std;

//Most of the functions are retrieved from the lecture slides and adapted for this case

template <class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree() : root(nullptr), ITEM_NOT_FOUND(nullptr)
{
}

template <class Key, class Value>
AVLSearchTree<Key, Value>::AVLSearchTree(const AVLSearchTree &rhs) : root(nullptr), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
    *this = rhs;
}

template <class Key, class Value>
AVLSearchTree<Key, Value>::~AVLSearchTree()
{
    makeEmpty();
}

template <class Key, class Value>
const Value &AVLSearchTree<Key, Value>::findMin() const
{
    return elementAt(findMin(root));
}

template <class Key, class Value>
const Value &AVLSearchTree<Key, Value>::findMax() const
{
    return elementAt(findMax(root));
}

template <class Key, class Value>
WordItem<Key, Value> *& AVLSearchTree<Key, Value>::findVal(const Key &x) const {
    return elementAt(find(x, root));
}


template <class Key, class Value>
bool AVLSearchTree<Key, Value>::isEmpty() const
{
    return root == nullptr;
}

//For debugging the AVLTree
template <class Key, class Value>
void AVLSearchTree<Key, Value>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty()
{
    makeEmpty(root);
}

//Insert function (public)
template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key &key, const Value &value)
{
    insert(key, value, root);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key &key)
{
    remove(key, root);
}

template <class Key, class Value>
const AVLSearchTree<Key, Value> &AVLSearchTree<Key, Value>::operator=(const AVLSearchTree &rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}



template <class Key, class Value>
WordItem<Key, Value>* &AVLSearchTree<Key, Value>::elementAt(WordItem<Key, Value> *t) const
{
    static WordItem<Key, Value>* ITEM_NOT_FOUND = nullptr;  // Initialize ITEM_NOT_FOUND here or in the constructor

    if (t == nullptr)
        return ITEM_NOT_FOUND;
    return t;
}



template <class Key, class Value>
void AVLSearchTree<Key, Value>::insert(const Key &key, const Value &value, WordItem<Key, Value> *&t)
{
    if (t == nullptr)
    {
        t = new WordItem<Key, Value>(key, value, nullptr, nullptr);
    }
    else if (key < t->key)
    {
        // Key should be inserted to the left tree
        insert(key, value, t->left);

        // Check if the left tree is out of balance (left subtree grew in height)
        if (height(t->left) - height(t->right) == 2)
        {
            if (key < t->left->key) // Key was inserted to the left-left subtree
                rotateWithLeftChild(t);
            else // Key was inserted to the left-right subtree
                doubleWithLeftChild(t);
        }
    }
    else if (t->key < key)
    { // Otherwise Key is inserted to the right subtree
        insert(key, value, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            // height of the right subtree increased
            if (t->right->key < key)
                // Key was inserted to right-right subtree
                rotateWithRightChild(t);
            else // Key was inserted to right-left subtree
                doubleWithRightChild(t);
        }
    }
    else
        ; // Duplicate; do nothing

    // update the height the node
    t->height = max(height(t->left), height(t->right)) + 1;
}

//Insert function (private)
template <class Key, class Value>
void AVLSearchTree<Key, Value>::remove(const Key &key, WordItem<Key, Value> *&t)
{
    if (t == nullptr)
        return; // Key not found; do nothing
    if (key < t->key)
        remove(key, t->left);
    else if (t->key < key)
        remove(key, t->right);
    else if (t->left != nullptr && t->right != nullptr) // Two children
    {
        t->key = findMin(t->right)->key;
        t->value = findMin(t->right)->value;
        remove(t->key, t->right);
    }
    else // one or no children
    {
        WordItem<Key, Value> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }

    if (t != nullptr)
        t->height = max(height(t->left), height(t->right)) + 1;
}


template <class Key, class Value>
void AVLSearchTree<Key, Value>::makeEmpty(WordItem<Key, Value> *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::printTree(WordItem<Key, Value> *t) const
{
    if (t != nullptr)
    {
        printTree(t->left);
        std::cout << "(" << t->key << ", " << t->value << ") ";
        printTree(t->right);
    }
}

template <class Key, class Value>
WordItem<Key, Value> *AVLSearchTree<Key, Value>::clone(WordItem<Key, Value> *t) const
{
    if (t == nullptr)
        return nullptr;
    return new WordItem<Key, Value>(t->key, t->value, clone(t->left), clone(t->right), t->height);
}

template <class Key, class Value>
int AVLSearchTree<Key, Value>::height(WordItem<Key, Value> *t) const
{
    if (t == nullptr)
        return -1;
    return t->height;
}

template <class Key, class Value>
int AVLSearchTree<Key, Value>::max(int lhs, int rhs) const
{
    if (lhs > rhs)
        return lhs;
    return rhs;
}


template <class Key, class Value>
WordItem<Key, Value>* AVLSearchTree<Key, Value>::findMin(WordItem<Key, Value>* t) const {
    if (t == nullptr)
        return nullptr;

    while (t->left != nullptr)
        t = t->left;

    return t;
}

template <class Key, class Value>
WordItem<Key, Value>* AVLSearchTree<Key, Value>::findMax(WordItem<Key, Value>* t) const {
    if (t == nullptr)
        return nullptr;

    while (t->right != nullptr)
        t = t->right;

    return t;
}



template <class Key, class Value>
WordItem<Key, Value>* AVLSearchTree<Key, Value>::find(const Key &x, WordItem<Key, Value> *t) const {
    while (t != nullptr) {
        if (x < t->key)
            t = t->left;
        else if (t->key < x)
            t = t->right;
        else
            return t; // Found
        // If not found, move to the appropriate subtree
    }
    return nullptr; // Not found
}






//AVL Manipulations to balance the AVLTree
template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithLeftChild(WordItem<Key, Value> *&k2) const
{
    WordItem<Key, Value> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::rotateWithRightChild(WordItem<Key, Value> *&k1) const
{
    WordItem<Key, Value> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithLeftChild(WordItem<Key, Value> *&k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class Key, class Value>
void AVLSearchTree<Key, Value>::doubleWithRightChild(WordItem<Key, Value> *&k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

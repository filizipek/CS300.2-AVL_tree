#ifndef AVL_SEARCH_TREE_H
#define AVL_SEARCH_TREE_H
#include <string>

template <class Key, class Value>
class AVLSearchTree;

//Used as an AVLNode in this case
template <class Key, class Value>
struct WordItem
{
    Key key;
    Value value;
    WordItem *left;
    WordItem *right;
    int height;

    //WordItem Constructor
    WordItem(const Key &theKey, const Value &theValue,
             WordItem *lt, WordItem *rt, int h = 0)
            : key(theKey), value(theValue), left(lt), right(rt), height(h) {}

    friend class AVLSearchTree<Key, Value>;
};

template <class Key, class Value>
class AVLSearchTree
{
public:
    AVLSearchTree();
    AVLSearchTree(const AVLSearchTree &rhs);
    ~AVLSearchTree();

    const Value &findMin() const;
    const Value &findMax() const;
    WordItem<Key, Value> *& findVal(const Key &x) const;
    bool isEmpty() const;
    void printTree() const;

    void makeEmpty();
    void insert(const Key &key, const Value &value);
    void remove(const Key &key);

    const AVLSearchTree &operator=(const AVLSearchTree &rhs);

private:
    WordItem<Key, Value> *root;
    const WordItem<Key, Value> * ITEM_NOT_FOUND;
    WordItem<Key, Value>* &elementAt(WordItem<Key, Value> *t) const;


    void insert(const Key &key, const Value &value, WordItem<Key, Value> *&t);
    void remove(const Key &key, WordItem<Key, Value> *&t);

    WordItem<Key, Value> *findMin(WordItem<Key, Value> *t) const;
    WordItem<Key, Value> *findMax(WordItem<Key, Value> *t) const;
    WordItem<Key, Value> *find(const Key &x, WordItem<Key, Value> *t) const;

    void makeEmpty(WordItem<Key, Value> *&t);
    void printTree(WordItem<Key, Value> *t) const;
    WordItem<Key, Value> *clone(WordItem<Key, Value> *t) const;

    // AVL manipulations
    int height(WordItem<Key, Value> *t) const;
    int max(int lhs, int rhs) const;
    void rotateWithLeftChild(WordItem<Key, Value> *&k2) const;
    void rotateWithRightChild(WordItem<Key, Value> *&k1) const;
    void doubleWithLeftChild(WordItem<Key, Value> *&k3) const;
    void doubleWithRightChild(WordItem<Key, Value> *&k1) const;
};

#include "AVLSearchTree.cpp"
#endif // AVL_SEARCH_TREE_H

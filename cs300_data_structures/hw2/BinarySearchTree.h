#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include <iostream>
using namespace std;

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode {
public:
    Comparable element;
    BinaryNode* left;
    BinaryNode* right; 
    BinaryNode(const Comparable& theElement,
    BinaryNode* lt, BinaryNode* rt):element(theElement), left(lt), right(rt) {}
    friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree {
public:
    BinarySearchTree();
    explicit BinarySearchTree(const Comparable& notFound);
    ~BinarySearchTree();
    Comparable& findMin() ;
    Comparable& findMax() ;
    Comparable& find(const Comparable& x);
    bool isEmpty() const;
    void printTree() const;
    void makeEmpty();
    void insert(const Comparable& x);
    void remove(const Comparable& x);
    BinarySearchTree<Comparable>& operator=(const BinarySearchTree<Comparable>& rhs);
    bool operator<(const Comparable& rhs);
    bool operator>(const Comparable& rhs);
private:
    BinaryNode<Comparable>* root;
    Comparable ITEM_NOT_FOUND;
    Comparable & elementAt(BinaryNode<Comparable>* t) ;
    void insert(const Comparable& x, BinaryNode<Comparable>*& t) ;
    void remove(const Comparable& x, BinaryNode<Comparable>*& t) ;
    BinaryNode<Comparable> * findMin(BinaryNode<Comparable>* t) ;
    BinaryNode<Comparable> * findMax(BinaryNode<Comparable>* t) ;
    BinaryNode<Comparable> * find(const Comparable& x, BinaryNode<Comparable>* t) ;
    void makeEmpty(BinaryNode<Comparable>*& t) const;
    void printTree(BinaryNode<Comparable>* t) const;
    BinaryNode<Comparable>* clone(BinaryNode<Comparable>* t) const;
};


template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() :root(nullptr), ITEM_NOT_FOUND(Comparable()) {}

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable& notFound) :
    ITEM_NOT_FOUND(notFound), root(NULL) {}

template <class Comparable>
Comparable& BinarySearchTree<Comparable>::elementAt(BinaryNode<Comparable>* t) { //gives where the element is if not found returns not found
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
Comparable& BinarySearchTree<Comparable>::find(const Comparable& x) //finding the wanted element
{
    return elementAt(find(x, root));
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::find(const Comparable& x, BinaryNode<Comparable>* t) //recursive find
{
    while (t != NULL)
        if (t->element > x)
            t = t->left;
        else if (t->element < x)
            t = t->right;
        else
            return t;    // Match

    return NULL;   // No match
}

template <class Comparable>
Comparable& BinarySearchTree<Comparable>::findMin() { //finding min element
    return elementAt(findMin(root));
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t) { //recursive min find
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}

template <class Comparable>
Comparable& BinarySearchTree<Comparable>::findMax() { //finding max element
    return elementAt(findMax(root));
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable>* t) { //recursive max find
    if (t != NULL)
        while (t->right != NULL)
            t = t->right;
    return t;
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x) { //inserting to a tree
    insert(x, root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode<Comparable>*& t) { //iterative insert
    BinaryNode<Comparable>* newNode = new BinaryNode<Comparable>(x, NULL, NULL);
    if (!root) root = newNode;
    else { 
        BinaryNode<Comparable>* curr = root;
        while (curr) {
            if (curr->element > x) {
                if (curr->left) curr = curr->left;
                else {
                    curr->left = newNode;
                    break;
                }
            }
            else if (curr->element < x) {
                if (curr->right) curr = curr->right;
                else {
                    curr->right = newNode;
                    break;
                }
            }
            else break;
        }
    }
 
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const { //true if empty tree
    return (root == nullptr);
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x) { //removes element 
    remove(x, root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode<Comparable>*& t) { //removes element recursively
    if (t == NULL)
        return;   // Item not found; do nothing
    if (t->element > x)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != NULL && t->right != NULL) { // Two children
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else {// one or no children
        BinaryNode<Comparable>* oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable>*& t) const { //emptying tree
    if (t != NULL) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTree() const { //printing tree
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
    makeEmpty();
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable>* t) const {//inorder traversal print
    if (t != NULL) {
        printTree(t->left);
        cout << t->element << endl;
        printTree(t->right);
    }
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::clone(BinaryNode<Comparable>* t) const { //clonening tree
    if (t == NULL)
        return NULL;
    else
        return new BinaryNode<Comparable>
        (t->element, clone(t->left), clone(t->right));
}

template <class Comparable>
bool BinarySearchTree<Comparable>::operator<(const Comparable& rhs) {
    if (this < rhs) return true;
    return false;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::operator>(const Comparable& rhs) {
    if (this > rhs) return true;
    return false;
}

template <class Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable>& rhs) { //= operator makes lhs same
    this->makeEmpty();
    this->root = rhs.clone(rhs.root);
    return *this;
}


#endif

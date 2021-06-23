#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>
using namespace std;

template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode{
    Comparable 	element;
    AvlNode* left;
    AvlNode* right;
    int height;
    AvlNode(const Comparable& theElement, AvlNode* lt, AvlNode* rt, int h = 0)
        : element(theElement), left(lt), right(rt), height(h) {}
    friend class AvlTree<Comparable>;
};

template <class Comparable>
class AvlTree{
public:
    AvlTree();
    explicit AvlTree(const Comparable& notFound);
    ~AvlTree();
    Comparable& findMin();
    Comparable& findMax();
    Comparable& find(const Comparable& x);
    bool isEmpty() const;
    void printTree() const;
    void makeEmpty();
    void insert(const Comparable& x);
    void remove(const Comparable& x);
    AvlTree<Comparable>& operator=(const AvlTree& rhs);
    bool operator<(const Comparable& rhs);
    bool operator>(const Comparable& rhs);
    void balance(AvlNode<Comparable>* N);

private:
    AvlNode<Comparable>* root;
    Comparable ITEM_NOT_FOUND;
    Comparable& elementAt(AvlNode<Comparable>* t);
    void insert(const Comparable& x, AvlNode<Comparable>*& t) const;
    void remove(const Comparable& x, AvlNode<Comparable>*& t);
    AvlNode<Comparable>* findMin(AvlNode<Comparable>* t);
    AvlNode<Comparable>* findMax(AvlNode<Comparable>* t);
    AvlNode<Comparable>* find(const Comparable& x, AvlNode<Comparable>* t);
    void makeEmpty(AvlNode<Comparable>*& t) const;
    void printTree(AvlNode<Comparable>* t) const;
    AvlNode<Comparable>* clone(AvlNode<Comparable>* t) const;

    // Avl manipulations
    int height(AvlNode<Comparable>* t) const;
    int max(int lhs, int rhs) const;
    void rotateWithLeftChild(AvlNode<Comparable>*& k2) const;
    void rotateWithRightChild(AvlNode<Comparable>*& k1) const;
    void doubleWithLeftChild(AvlNode<Comparable>*& k3) const;
    void doubleWithRightChild(AvlNode<Comparable>*& k1) const;
};


template <class Comparable>
AvlTree<Comparable>::AvlTree() :root(nullptr), ITEM_NOT_FOUND(Comparable()) {}

template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable& notFound) :
    ITEM_NOT_FOUND(notFound), root(NULL) {}

template <class Comparable>
Comparable& AvlTree<Comparable>::elementAt(AvlNode<Comparable>* t) {//gives where the element is if not found returns not found
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
Comparable& AvlTree<Comparable>::find(const Comparable& x)//finding the wanted element
{
    return elementAt(find(x, root));
}

template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::find(const Comparable& x, AvlNode<Comparable>* t) //recursive find
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
Comparable& AvlTree<Comparable>::findMin() {
    return elementAt(findMin(root));
}

template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMin(AvlNode<Comparable>* t) { //find min value on tree
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}

template <class Comparable>
Comparable& AvlTree<Comparable>::findMax() {
    return elementAt(findMax(root));
}

template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMax(AvlNode<Comparable>* t) { //finds max value on tree
    if (t != NULL)
        while (t->right != NULL)
            t = t->right;
    return t;
}

template <class Comparable>
int AvlTree<Comparable>::height(AvlNode<Comparable>* t) const{ //returns the height of the tree if nothing then -1
    if (t == NULL)
        return -1;

    return t->height;
}

template <class Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) //returns the max one from two parameters
const {
    if (lhs > rhs)
        return lhs;

    return rhs;
}

template <class Comparable>
void AvlTree<Comparable>::insert(const Comparable& x) {
    insert(x, root);
}

template <class Comparable>
void AvlTree<Comparable>::insert
(const Comparable& x, AvlNode<Comparable>*& t) const { //inserts to avl tree
    if (t == NULL)
        t = new AvlNode<Comparable>(x, NULL, NULL);

    else if (t->element>x) { // x to left 
       
        insert(x, t->left);

        if (height(t->left) - height(t->right) == 2) // check if the left tree is not balanced
            if (t->left->element>x)  // x inserted to left left 
                rotateWithLeftChild(t);
            else			     // x inserted to left right
                doubleWithLeftChild(t);
    }
    else if (t->element < x) //x to right
    {    
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2) // height of the right is not balanced
           
            if (t->right->element < x)// x inserted to right right
                
                rotateWithRightChild(t);
            else // x inserted to right left
                doubleWithRightChild(t);
    }
    else;  // Duplicate; do nothing

 
    t->height = max(height(t->left), height(t->right)) + 1; // updates the height of nodes
}

template <class Comparable> 
void AvlTree<Comparable>::rotateWithLeftChild( AvlNode<Comparable>*& k2) const{ //rotate with left
    AvlNode<Comparable>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild //rotate with right
(AvlNode<Comparable>*& k1) const
{
    AvlNode<Comparable>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild //rotate with right then left 
(AvlNode<Comparable>*& k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild //rotate with left then right
(AvlNode<Comparable>*& k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

template <class Comparable>
bool AvlTree<Comparable>::isEmpty() const {
    return (root == nullptr);
}

template <class Comparable>
void AvlTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

template <class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable>*& t) const { //emptys tree
    if (t != NULL) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}

template <class Comparable>
void AvlTree<Comparable>::printTree() const {
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

template <class Comparable>
AvlTree<Comparable>::~AvlTree() {
    makeEmpty();
}

template <class Comparable>
void AvlTree<Comparable>::printTree(AvlNode<Comparable>* t) const {//inorder print
    if (t != NULL) {
        printTree(t->left);
        cout << t->element << endl;
        printTree(t->right);
    }
}

template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::clone(AvlNode<Comparable>* t) const { //clones tree
    if (t == NULL)
        return NULL;
    else
        return new AvlNode<Comparable>
        (t->element, clone(t->left), clone(t->right));
}

static const int ALLOWED_IMBALANCE = 1; //the max imbalance one node can have 

template <class Comparable>
void AvlTree<Comparable>::balance(AvlNode<Comparable>* t) { //checks the balance if tree and if not balanced rotates accordingly
    if (t == NULL) return ; 
    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) //left is much higher imbalance situation
        if (height(t->left->left) >= height(t->left->right)) //checking lefts left and lefts right then do rotation
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    else
         if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) //right is much higher - imbalance situation
         if (height(t->right->right) >= height(t->right->left)) //checking right right and right left then do rotations accordingly
        rotateWithRightChild(t);
     else
         doubleWithRightChild(t);
        t->height = max(height(t->left), height(t->right)) + 1;
}

template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable& x) {
    remove(x, root);
}

template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable& x, AvlNode<Comparable>*& t) { //removing from tree
    if (t == NULL) ;   
    if (t->element > x) remove(x, t->left);
    else if (t->element < x) remove(x, t->right);      
    else if (t->left != NULL && t->right != NULL) { //if two children
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else {//if one or no children
        AvlNode<Comparable>* oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }

    balance(t); //after deleting we update all hight and check balance 
    //if it is not balanced we rotate it accordingly 
}

template <class Comparable>
bool AvlTree<Comparable>::operator<(const Comparable& rhs) {
    if (this < rhs) return true;
    return false;
}

template <class Comparable>
bool AvlTree<Comparable>::operator>(const Comparable& rhs) {
    if (this > rhs) return true;
    return false;
}

template <class Comparable>
AvlTree<Comparable>& AvlTree<Comparable>::operator=(const AvlTree<Comparable>& rhs) { //= operator makes lhs same
    this->makeEmpty();
    this->root = rhs.clone(rhs.root);
    return *this;
}

#endif

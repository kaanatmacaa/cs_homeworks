#include "BinaryTree.h"
#include <iostream>

using namespace std;


template <class myType>
BinaryTree<myType>::BinaryTree(){ //Constructor
  root = nullptr;
}


template <class myType>
BinaryTree<myType>::BinaryTree(const BinaryTree<myType>& rhs){ //Copy Constructor
  
  root = nullptr;
  Iterator<myType> iter;
  iter.Init(rhs);
    
  while(iter.hasNext()){
    this->insert(iter.InOrderNext()->value);
  }
}


template <class myType>
BinaryTree<myType>::~BinaryTree(){ //Destructor
  Iterator<myType> iter;
  iter.Init(*this);
    
  while(iter.hasNext()){
    delete iter.InOrderNext();
  }
}


template <class myType>
TreeNode<myType>* BinaryTree<myType>::getRoot(){
  return this->root;
}

//First create the new node with the given value
template <class myType>
void BinaryTree<myType>::insert(myType num) {
  TreeNode<myType>*newNode,	// Pointer to a new node
    *nodePtr;	// Pointer to traverse the tree
  
  // Create a new node
  newNode = new TreeNode<myType>;
  newNode->value = num;
  newNode->left = newNode->right = nullptr;
  
  if (!root)	// Is the tree empty?
    root = newNode;
  else 
    {
      //we have a root, need to find the location for the next item
      nodePtr = root; 
      while (nodePtr) {
	if (num < nodePtr->value) {
	  if (nodePtr->left)
	    nodePtr = nodePtr->left;
	  else {
	    nodePtr->left = newNode;
	    break;
	  }
	}
	else if (num > nodePtr->value) {
	  if (nodePtr->right)
	    nodePtr = nodePtr->right;
	  else {
	    nodePtr->right = newNode;
	    break;
	  }
	}
	else { //num is not greater or smaller. So it is equal
	  cout << "Duplicate value found in tree.\n";
	  break;
	}
      }		
    }
}


///OPERATORS///////////////////////
template <class myType>
const BinaryTree<myType>& BinaryTree<myType>::operator= (const BinaryTree& rhs){
  if(this!=&rhs)
    {
      this->~BinaryTree();
      this->root = nullptr;
      
      Iterator<myType> iter;
      iter.Init(rhs);
      while (iter.hasNext()) {
	this->insert(iter.Next()->value);
      }
    }
  return *this;
}

template <class myType>
bool BinaryTree<myType>::operator== (const BinaryTree<myType>& rhs){
  if(this != &rhs){
    Iterator<myType> iter_lhs, iter_rhs;
    iter_lhs.Init(*this);
    iter_rhs.Init(rhs);
    while (iter_lhs.hasNext() && iter_rhs.hasNext()) {
      if(iter_lhs.Next()->value != iter_rhs.Next()->value){
	return false;
      }
    }
    if(iter_lhs.hasNext() || iter_rhs.hasNext()){
      return false;
    }
  }
  return true;
}

template <class myType>
bool BinaryTree<myType>::operator!= (const BinaryTree& rhs){
  return !operator==(rhs);
}

template <class myType>
void BinaryTree<myType>::operator+=(myType number){
  this->insert(number);
}

template <class myType>
void BinaryTree<myType>::operator+=(const BinaryTree<myType>& rhs){
  Iterator<myType> iter;
  iter.Init(rhs);
  while (iter.hasNext()) {
    this->insert(iter.Next()->value);
  }
}

template <class myType>
BinaryTree<myType> BinaryTree<myType>::operator+(const BinaryTree<myType>& rhs){
  BinaryTree temp(*this);
  temp += rhs;
  return temp;
}

template <class myType>
BinaryTree<myType> BinaryTree<myType>::operator+(myType number){
  BinaryTree temp(*this);
  temp.insert(number);
  return temp;
}

template <class myType>
BinaryTree<myType> operator+(myType number, const BinaryTree<myType>& tree){
  BinaryTree<myType> temp(tree);
  temp.insert(number);
  return temp;
}


template <class myType>
ostream & operator<< (ostream & os, const BinaryTree<myType>& rhs)
{
  Iterator<myType> iter;
  iter.Init(rhs);
  while (iter.hasNext()) {
    os << iter.Next()->value << " ";
  }
  os << endl;
  return os;
}

//////END OF OPERATORS/////////////////////



 ///////////// ITERATOR CLASS/////////
 
template <class myType>
Iterator<myType>::Iterator()
  :myCurrent(nullptr), stack(nullptr), stack2(nullptr)
{}

template <class myType>
void Iterator<myType>::Init(const BinaryTree<myType>&tree)
{
  myCurrent = tree.root;
  stack = new Stack<myType>;
}

template <class myType>
bool Iterator<myType>::hasNext()
{
  return (!stack->isEmpty() || myCurrent != nullptr);
}

template <class myType>
TreeNode<myType>* Iterator<myType>::Next()
{
  while (myCurrent != nullptr) {
    stack->push(myCurrent);
    myCurrent = myCurrent->left;
  }
  
  myCurrent = stack->pop();
  TreeNode<myType>* node = myCurrent;
  myCurrent = myCurrent->right;
  
  return node;
}

template <class myType>
TreeNode<myType>* Iterator<myType>::InOrderNext()
{
  while (myCurrent != nullptr) {
    stack->push(myCurrent);
    myCurrent = myCurrent->left;
  }
  
  myCurrent = stack->pop();
  TreeNode<myType>* node = myCurrent;
  myCurrent = myCurrent->right;
  
  return node;
}

////END OF ITERATOR///////////////////
//
//This is just to show. Iterative post-order is much more complex.
//
//template <class myType>
//TreeNode* Iterator<myType>::PreOrderNext()
//{
//  if(myCurrent->left != nullptr || myCurrent->right != nullptr){
//    stack->push(myCurrent);
//  }
//  
//  TreeNode* node = myCurrent;
//
//  if(myCurrent->left == nullptr && myCurrent->right == nullptr){
//    if(!stack->isEmpty()){
//      myCurrent = stack->pop();
//    }
//    else{
//      myCurrent = nullptr;
//      return node;
//    }
//    if(myCurrent->right){
//      myCurrent = myCurrent->right;
//    }
//    else{
//      while(!myCurrent->right){
//	myCurrent = stack->pop();
//	myCurrent = myCurrent->right;
//      }
//    }   
//  }
//  else if(myCurrent->left){
//    myCurrent = myCurrent -> left;
//  }
//  else if(myCurrent->right){
//    myCurrent = stack->pop();
//    myCurrent = myCurrent -> right;
//  }
//
//  return node;
//}

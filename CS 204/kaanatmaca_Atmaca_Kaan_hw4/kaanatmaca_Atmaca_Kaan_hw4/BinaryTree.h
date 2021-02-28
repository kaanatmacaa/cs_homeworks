#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include "Stack.h"

using namespace std;

template <class myType> 
class BinaryTree
{
 public:
  
  BinaryTree();//Constructor
  
  BinaryTree(const BinaryTree<myType>&);//Copy Constructor

  ~BinaryTree();  //Destructor
  
  //Insertion method
  void insert(myType);
  TreeNode<myType>* getRoot();
  
  //operators
  const BinaryTree<myType>& operator= (const BinaryTree<myType>& rhs);
  bool operator== (const BinaryTree<myType>& rhs);
  bool operator!= (const BinaryTree<myType>& rhs);
  void operator+= (myType number);
  void operator+= (const BinaryTree<myType>& rhs);

  BinaryTree<myType> operator+ (const BinaryTree<myType>& rhs);
  
  BinaryTree<myType>  operator+( myType number);
  
  template <class myType>
  friend BinaryTree<myType> operator+(myType number, const BinaryTree<myType>&);
  
  template <class myType>
  friend ostream& operator<<(ostream&, const BinaryTree<myType>&);

 private:
  TreeNode<myType>* root;  //The root of the tree

  template <class myType>
  friend class Iterator;
};

template <class myType>
class Iterator{
 public:
  Iterator();  //Constructor
  void Init(const BinaryTree<myType>& );
  bool hasNext();
  TreeNode<myType>* Next(); //Actually the same with InOrderNext()
  TreeNode<myType>* InOrderNext(); 
 /* TreeNode<myType>* PreOrderNext(); */

 private:
  TreeNode<myType>* myCurrent;
  Stack<myType>* stack;
  Stack<myType>* stack2;
};

#include "BinaryTree.cpp"
#endif

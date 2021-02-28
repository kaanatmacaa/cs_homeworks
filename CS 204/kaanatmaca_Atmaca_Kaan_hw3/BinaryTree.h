#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include "Stack.h"

using namespace std;

class BinaryTree
{
 public:
  
  BinaryTree();//Constructor
  BinaryTree(const BinaryTree&); //Copy Constructor
  ~BinaryTree();//Destructor
  void insert(int);  // Insertion method

  /////////operators 
	friend ostream& operator<<(ostream&, const BinaryTree&); //prints content in order 
	const BinaryTree& operator=(const BinaryTree&); //lhs = rhs 
	friend bool operator==(const BinaryTree&, const BinaryTree&); //true if lhs == rhs 
	friend bool operator!=(const BinaryTree&, const BinaryTree&); // true if lhs != rhs 
	const BinaryTree& operator+=(const BinaryTree&); // adds this and rhs and returns new added binary tree 
	const BinaryTree& operator+(const BinaryTree&); //adds two trees returns then sum 
	const BinaryTree& operator+=(const int&); //adds an int to a tree
	friend const BinaryTree operator+(const BinaryTree&, const int&); //tree + int 
	friend const BinaryTree operator+(const int&, const BinaryTree&); //int + tree 
 ////////////////
  
private:
	TreeNode* root; //The root of the tree
	friend class Iterator;
	void copyConstructerHelper(TreeNode*, TreeNode*&);  //recursive copyconst helper 
	void destructerHelper(TreeNode*); //recursive destruct helper 
	TreeNode* insertHelper(int, TreeNode*); //recursive insert helper 
};

class Iterator{
public:
  Iterator();  //Constructor
  void Init(const BinaryTree& ); //inits
  bool hasNext(); //returns true if node 
  TreeNode* Next(); //returns next node 
  void InitHelper(TreeNode*, Stack*); //recursive init helper 
  
private:

  TreeNode* myCurrent;
  Stack* stack;
 
};

#endif

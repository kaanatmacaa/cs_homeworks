#include "BinaryTree.h"
#include <iostream>

using namespace std;

//Constructor
BinaryTree::BinaryTree(){
	root = nullptr; 
}

void BinaryTree::copyConstructerHelper(TreeNode* copyFrom, TreeNode* &copyTo) { //recursive function for copy constructer -helper 
	if (copyFrom == nullptr) {
		copyTo == nullptr;
	}
	else {
		copyTo = new TreeNode;
		copyTo->value = copyFrom->value;
		copyConstructerHelper(copyFrom->left, copyTo->left);
		copyConstructerHelper(copyFrom->right, copyTo->right);
	}
}

BinaryTree::BinaryTree(const BinaryTree& rhs){//TODO: Implement deep copy constructor use iterator 
	TreeNode* copyTo = nullptr; 
	TreeNode* copyFrom = rhs.root;
	copyConstructerHelper(copyFrom, copyTo);
	this->root = copyTo;
}

void BinaryTree::destructerHelper(TreeNode* currRoot) { //recursive function for destructer -helper 
	if (currRoot != nullptr) {
		destructerHelper(currRoot->left);
		destructerHelper(currRoot->right);
		delete currRoot;
	}
}

BinaryTree::~BinaryTree(){//Destructor
	destructerHelper(root);
}

TreeNode* BinaryTree::insertHelper(int num, TreeNode* root) { //recursive function for insert -helper 
	if (root == nullptr) {
		root = new TreeNode();
		root->value = num;
		return root;
	}
	else {
	TreeNode* curr;
	if (root->value > num) {
		curr = insertHelper(num, root->left);
		root->left = curr;
	}
	else if (root->value < num) {
		curr = insertHelper(num, root->right);
		root->right = curr;
		}
	else if (root->value == num) {
		cout << "Duplicate value found in tree." << endl;
	}
	return root;
	}
}

void BinaryTree::insert(int num) { //TODO: Implement insert function for BinaryTree
	root = insertHelper(num, root);
}



//Operators //Give the implementations of operators in here either as free function or member function
const BinaryTree& BinaryTree::operator=(const BinaryTree& rhs){ //will return this = rhs
	
	if (this != &rhs){
		this->destructerHelper(this->root);
		this->root = nullptr;
		Iterator I;
		I.Init(rhs);
		while (I.hasNext()) {
			this->insert(I.Next()->value);
		}
	}

	return *this;
}

const BinaryTree& BinaryTree::operator+(const BinaryTree& rhs){ //will add this and rhs and return this
	BinaryTree result;
	Iterator I;
	I.Init(rhs);
	while (I.hasNext()) {
		this->insert(I.Next()->value);
	}
	return *this;
}

const BinaryTree& BinaryTree::operator+=(const BinaryTree& rhs) { //will add this and rhs and return this
	Iterator I;
	I.Init(rhs);
	while (I.hasNext()) {
		this->insert(I.Next()->value);
	}
	return *this;
}

const BinaryTree& BinaryTree::operator+=(const int& rhs) {
	this->insert(rhs);
	return *this;
}


//friend operators //////////////////////////
ostream& operator<<(ostream& os, const BinaryTree& rhs) { //is used to cout a BinaryTree and then returns os (cout) 
	if (rhs.root != nullptr) {
	Iterator I;
	I.Init(rhs);
	while (I.hasNext()) {
		os << I.Next()->value << " ";
	}
	os << endl;
	}
	return os;
}

bool operator==(const BinaryTree& lhs, const BinaryTree& rhs) { //true if lhs ==rhs
	return (&lhs == &rhs);
}

bool operator!=(const BinaryTree& lhs, const BinaryTree& rhs) { //true if lhs !=rhs
	return (&lhs != &rhs);
}

const BinaryTree operator+(const BinaryTree& lhs, const int & rhs) { //returns binarytree result by adding to binary tree and int
	BinaryTree result; 
	Iterator I; 
	I.Init(lhs);
	while (I.hasNext()) {
		result.insert(I.Next()->value);
	}
	result.insert(rhs);
	return result;
}

const BinaryTree operator+(const int& lhs,const BinaryTree& rhs) { //returns binarytree result by adding to binary tree and int
	BinaryTree result;
	Iterator I;
	I.Init(rhs);
	while (I.hasNext()) {
		result.insert(I.Next()->value);
	}
	result.insert(lhs);
	return result;
}



///////////////////////////////////  ITERATOR CLASS

Iterator::Iterator()//Constructor
  :myCurrent(nullptr), stack(nullptr)
{}

void Iterator::InitHelper(TreeNode* root, Stack* stack){ //for iterator recursice func 
	if (root == nullptr) return;
	InitHelper(root->right, stack);
	stack->push(root);
	InitHelper(root->left, stack);
}

void Iterator::Init(const BinaryTree &tree){ //to initilize iterator 
  myCurrent = tree.root;
  stack = new Stack();
  InitHelper(myCurrent,stack);
}



bool Iterator::hasNext() { //Returns true if tree has more nodes to explore
	return(!(stack->isEmpty()));
}


TreeNode* Iterator::Next() //TODO: Implement next function of the iterator//Next node to explore
{	
	TreeNode* node; 
	node = stack->pop();
    return node;//Note that it returns the next element
}





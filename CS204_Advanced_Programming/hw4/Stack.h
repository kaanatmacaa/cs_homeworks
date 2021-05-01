#ifndef _STACK_H
#define _STACK_H

#include <iostream>

template <class myType>
struct TreeNode
{
  myType value;
  TreeNode<myType> *left;
  TreeNode<myType> *right;

  TreeNode(){
    left = nullptr;
    right = nullptr;
  }
};

template <class myType>
struct StackNode
{
  TreeNode<myType>* value;
  StackNode<myType>*next;
};

template <class myType>
class Stack
{
private:
  StackNode<myType>*top;
  StackNode<myType>* GetTopPointer(Stack myStack);
  
public:
  Stack();
  void push(TreeNode<myType>* );
  TreeNode<myType>* pop();
  bool isEmpty();
};

#include "Stack.cpp"
#endif

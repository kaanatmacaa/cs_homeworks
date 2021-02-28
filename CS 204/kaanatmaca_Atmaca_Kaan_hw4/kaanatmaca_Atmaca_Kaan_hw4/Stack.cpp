#include <iostream>
#include "Stack.h"
using namespace std;


template <class myType>
Stack<myType>::Stack()//Constructor
{
	top=nullptr;
}


template <class myType>
StackNode<myType>* Stack<myType>::GetTopPointer(Stack<myType> myStack)
{
	return myStack.top;
}



template <class myType>
void Stack<myType>::push(TreeNode<myType>* elmt) //Push back elements to the stack
{
	StackNode<myType>*newNode;

	newNode = new StackNode<myType>;
	newNode->value = elmt;

	if(isEmpty())
	{
		top = newNode;
		newNode->next = nullptr;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}
//Pop up elements from the stack

template <class myType>
TreeNode<myType>* Stack<myType>::pop()
{
	StackNode<myType> *temp;

	if(!isEmpty())
	{
		TreeNode<myType>* elmt = top->value;
		temp = top->next;
		delete top;
		top = temp;
		return elmt;
	}
	return nullptr;
}

//If the stack is empty check function

template <class myType>
bool Stack<myType>::isEmpty()
{
	return (top==nullptr);
}

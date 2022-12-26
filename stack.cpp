#include "stack.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

stack::stack()
{
	head = NULL;
	stackCounter = 0;

}

void stack::push(string str)
{
	node* n = new node(str);
	n->next = head;
	head = n;
}

bool stack::pop()
{
	if (head == NULL)
	{
		cout << "ERROR" << endl;
		return false;
	}
	else
	{

		node* n = new node;
		n = head;
		head = head->next;
		delete n;
		return true;
	}
	

}

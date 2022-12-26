#pragma once
#include "node.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class stack
{
public:
	node* head;
	int stackCounter;
	stack();
	void push(string);
	bool pop();




};
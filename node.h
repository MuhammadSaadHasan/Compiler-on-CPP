#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class node
{
public:
	string tag;
	char val;
	node* next;

	node();
	node(string);
	node(char);

	int lengthOfTag();



};
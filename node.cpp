#include "node.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

node::node(string str)
{
	tag = str;
	next = NULL;
}

int node::lengthOfTag()
{
	int n = tag.length();
	return n;
}
node::node()
{
	next = NULL;
}


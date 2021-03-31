#include <iostream>
#include "KnowledgeBase.h"
#include "BinaryRelation.h"
#include "Pair.h"
using std::cin; 
using std::cout; 
using std::endl; 

int main()
{
	BinaryRelation<int, string> relation1; 

	relation1.addRelation(Pair<int, string>(1, "one"));
	relation1.addRelation(Pair<int, string>(2, "two"));
	relation1.addRelation(Pair<int, string>(3, "three"));
	relation1.addRelation(Pair<int, string>(4, "four"));

	cout << relation1 << endl; 
	cout << !relation1 << endl; 

	BinaryRelation<int, string> relation2; 
	relation2.addRelation(Pair<int, string>(5, "five"));
	relation2.addRelation(Pair<int, string>(6, "six"));
	relation2.addRelation(Pair<int, string>(7, "seven"));

	cout << relation2 << endl; 

	cout << relation1 + relation2 << endl;
	cout << (relation1 ^ relation2) << endl; 

	BinaryRelation<string, string> relation3; 
	relation3.addRelation(Pair<string, string>("five", "fifth"));
	relation3.addRelation(Pair<string, string>("six", "sixth"));
	relation3.addRelation(Pair<string, string>("seven", "seventh"));

	cout << relation3 << endl; 
	cout << relation2 * relation3 << endl;

	if (relation1.r(1, "one"))
	{
		cout << "In relation." << endl;
	}
	else
	{
		cout << "Not in relation." << endl; 
	}

	if (relation2.r(1, "one"))
	{
		cout << "In relation." << endl;
	}
	else
	{
		cout << "Not in relation." << endl;
	}

	if (relation1.injection())
	{
		cout << "this relation is injection." << endl; 
	}
	else
	{
		cout << "this relation is not injection." << endl;
	}

	if (relation1.function())
	{
		cout << "this relation is a partial function." << endl;
	}
	else
	{
		cout << "this relation is not a partial function." << endl;
	}


	return 0; 
}
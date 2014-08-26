#pragma once
#include<iostream>
using namespace std;

class Arc
{
	int destination;
	int weight;

public:
	Arc();
	Arc(int a, int b);
	int getWeight();
	int getDestination();
	friend istream& operator>>(istream& in, Arc& arc);
	~Arc(void);
};

#pragma once
#include <set>
#include "Arc.h"
#include<iostream>
using namespace std;

class Nod
{
	int value,longitude, latitude, dist;
	Nod*pred;
	set<Arc*> arcs;
public:
	Nod();
	Nod(int ,int ,int);
	int getDist();
	void setPred(Nod* pred, int dist);
	Nod* getPred();
	int getValue();
	set<Arc*>& getArcs();
	void printPath();
	~Nod(void);

	void AddArc(Nod *nod, int length);
	friend istream& operator>>(istream& in, Nod& nod);
	friend ostream& operator<<(ostream& out, Nod nod);
};

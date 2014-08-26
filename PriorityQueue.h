#pragma once
#include "Nod.h"
#include<vector>

class PriorityQueue
{
	vector<Nod*> elements;
public:
	PriorityQueue(void);
	void insert(Nod* item);
	Nod* extractMin();
	void shift(int first, int last);
	void buildHeap();
	~PriorityQueue(void);
};

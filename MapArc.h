#pragma once
#include "Nod.h"

class Nod;

class MapArc
{
	Nod* destination;
	int length;
public:
	MapArc(Nod* arcDestination,int arcLength);
	~MapArc(void);

	Nod* GetDestination();
	int GetLength();
};

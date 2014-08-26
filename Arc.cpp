#include "Arc.h"

Arc::Arc()
{
}

Arc::Arc(int a, int b) {
	this->destination = a;
	this->weight = b;
}

int Arc:: getDestination()
{
	return destination;
}

int Arc:: getWeight()
{
	return weight;
}

Arc::~Arc(void)
{
}

istream& operator>>(istream& in, Arc& arc)
{
	return in>>arc.destination>>arc.weight;
}

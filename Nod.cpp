#include "Nod.h"
#include <limits.h>
Nod::Nod()
{
	this->pred=NULL;
	this->dist=INT_MAX;
}

Nod::Nod(int a, int b, int c) {
	this->value = a;
	this->latitude = b;
	this->longitude = c;

	this->pred=NULL;
	this->dist=INT_MAX;
}

int Nod:: getDist()
{
	return this->dist;
}

void Nod:: setPred(Nod* pred, int dist)
{
	this->pred=pred;
	this->dist=dist;
}

Nod* Nod:: getPred()
{
	return this->pred;
}

int Nod:: getValue()
{
	return this->value;
}

set<Arc*>& Nod:: getArcs()
{
	return this->arcs;
}

void Nod::printPath()
{
	if(pred)
		pred->printPath();
	cout<<this->value<<"->";
}

Nod::~Nod(void)
{
}

istream& operator>>(istream& in, Nod& nod)
{
	in>>nod.value>>nod.longitude>>nod.latitude;
	int n;
	in>>n;
	int destination, weigth;
	for(int i=0;i<n;i++)
	{
		Arc *temp=new Arc;
		in>>(*temp);
		nod.arcs.insert(temp);
	}

	return in;
}

ostream& operator<<(ostream& out, Nod nod) {
	out<<"Nod: val[ "<<nod.getValue()<<" ] "<<endl;
	return out;
}

void Nod::AddArc(Nod *nod, int length) {
	arcs.insert(new Arc(nod->value, length));
}
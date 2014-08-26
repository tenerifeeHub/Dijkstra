#include<iostream>
#include<map>
#include<ctime>
#include "Markup.h"
#include "PriorityQueue.h"

#include "Map.h"

using namespace std;

void getDistances(map<int, Nod*>& nodes, Nod* source, Nod* destination)
{
	PriorityQueue pq;
	source->setPred(NULL, 0);

	clock_t t = clock();

	while(source!=NULL)
	{
		if(source == destination)
		{
			cout<<"Time: "<<clock()-t<<endl;
			destination->printPath();
			cout<<"\b\b  \nTotal distance: "<<destination->getDist();
			return;
		}
		for(set<Arc*>::iterator it=source->getArcs().begin();it!=source->getArcs().end();++it)
		{
			Nod *y=nodes[(*it)->getDestination()];
			int value=source->getDist()+(*it)->getWeight();

			if(value < y->getDist())
			{
				y->setPred(source, value);
				pq.insert(y);
			}
		}
		source=pq.extractMin();		
	}
}

void main()
{
	Map map;
	clock_t t = clock();

	//map.Read("smallXML.xml");
	map.CMarkupRead("smallXML.xml");

	t = clock()-t;
	cout<<"Read Time: "<<t<<endl;

	int s,d;
	cout<<"Type the source node:"<<endl;
	cin>>s;
	cout<<"Type the destination node"<<endl;
	cin>>d;

	Nod* source=(*map.getMap())[s];
	Nod* destination=(*map.getMap())[d];

	getDistances(*map.getMap(), source, destination);

	//map.Write("output.txt");

}
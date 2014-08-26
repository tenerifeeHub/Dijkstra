#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(void)
{
}

void PriorityQueue::insert(Nod* item)
{
	elements.push_back(item);
	shift(0, elements.size()-1);
}

Nod* PriorityQueue::extractMin()
{
	if(elements.empty()==true)
	{
		return NULL;
	}

	int last=elements.size()-1;
	Nod* tmp=elements[0];
	while(tmp==elements[0])
	{
		elements[0]=elements[last];
		elements.pop_back();
		if(elements.size()==0)
		{
			break;
		}

		shift(0, last-1);
		last--;
	}
	
	return tmp;
}

void PriorityQueue::shift(int first, int last)
{
	int leftChild ,rightChild ,swapIndex;
	leftChild=2*first;
	rightChild=2*first+1;

	if (leftChild<=last && elements[leftChild]->getDist()<elements[first]->getDist())
	{
		swapIndex=leftChild;
	}
	else 
	{
		swapIndex=first;
	}

	if (rightChild<=last && elements[rightChild]->getDist()<elements[swapIndex]->getDist())
	{
		swapIndex=rightChild;
	}

	if (swapIndex!=first)
	{
		Nod* aux;
		aux=elements[first];
		elements[first]=elements[swapIndex];
		elements[swapIndex]=aux;
		shift(swapIndex,last);
	}
}

void PriorityQueue::buildHeap()
{
	int size=elements.size();
	int middleIndex=elements.size();

	while(middleIndex>=0)
	{
		shift(middleIndex, size-1);
		--middleIndex;
	}
}

PriorityQueue::~PriorityQueue(void)
{
}

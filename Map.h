#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<queue>
#include "Markup.h"
#include "Nod.h"

using namespace std;

class Map
{
	typedef void (*LineAnalizer) (char*, int&, Map& map);

	LineAnalizer analizer;
	void AnalizeLine(char* line);
	friend void LineStart(char* line, int& i, Map& map);
	friend void StartTag(char* line, int& i, Map& map);
	friend void NodeAnalizer(char* line, int& i, Map& map);
	friend void ArcAnalizer(char* line, int& i, Map& map);

	char** possibleTags;
	LineAnalizer *tagAnalizer;
	int tagsN;

	map<int,Nod*> nodes;
	
	void AddNode(int key,Nod* nod);
	void AddArc(int from,int to,int length);
public:
	Map();
	~Map();

	void Read(char* fileName);
	void Write(char* fileName);

	void CMarkupRead(char* fileName);

	map<int, Nod*>* getMap();
};

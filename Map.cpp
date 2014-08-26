#include "Map.h"

Map::Map()
{
	tagsN = 3;
	possibleTags = new char*[tagsN];
	tagAnalizer = new LineAnalizer[tagsN];

	possibleTags[0] = "nodes";
	possibleTags[1] = "node";
	possibleTags[2] = "arc";

	tagAnalizer[0] = NULL;
	tagAnalizer[1] = NodeAnalizer;
	tagAnalizer[2] = ArcAnalizer;
}

Map::~Map()
{

}

bool IsSpace(char test)
{
	return test == ' ' || test == '>' || test == '/' || test == '=';
}


char* PassWord(char* line,int& i)
{
	char* tag;
	for(int j=i;j<strlen(line);j++)
	{
		if(IsSpace(line[j]))
		{
			tag = new char[j-i+1];
			strncpy(tag,line+i,j-i);
			tag[j-i] = '\0';
			i = j;
			return tag;
		}
	}
}

int PassNumber(char* line,int &i)
{
	if(line[i] == '"')
	{
		int number = 0;
		for(i++;i<strlen(line);i++)
		{
			if(line[i] == '"')
			{
				i++;
				return number;
				break;
			}
			number = number*10+(line[i]-'0');
		}
	}
	throw "Expecting \"";
}

void PassSpaces(char* line,int& i)
{
	for(;i<strlen(line);i++)
	{
		if(line[i] != ' ')
		{
			return;
		}
	}
}

void Find(char* line,int &i,char lookFor)
{
	for(;i<strlen(line);i++)
	{
		if(line[i] == lookFor)
		{
			i++;
			return;
		}
	}
}

void StartTag(char* line, int& i, Map& map)
{
	char* tag = PassWord(line,i);

	for(int j=0;j<map.tagsN;j++)
	{
		if(strcmp(map.possibleTags[j],tag)==0)
		{
			map.analizer = map.tagAnalizer[j];
			return;
		}
	}
	map.analizer = NULL;
}

long* FillAttributes(char* line, int& i, Map & map,char** attributes)
{
	long* values = new long[3];

	values[0] = 0;
	values[1] = 0;
	values[2] = 0;

	int valuedAttribute = 0;

	PassSpaces(line,i);
	while(!IsSpace(line[i]))
	{		
		char* attribute = PassWord(line,i);

		for(int j=0;j<3;j++)
		{
			if(strcmp(attributes[j],attribute)==0)
			{
				valuedAttribute = j;
				break;
			}
		}

		PassSpaces(line,i);
		Find(line,i,'=');
		PassSpaces(line,i);
		int value = PassNumber(line,i);

		values[valuedAttribute] = value;
		PassSpaces(line,i);
	}
	return values;
}

void ArcAnalizer(char* line, int& i, Map& map)
{
	char** attributes = new char*[3];

	attributes[0] = "from";
	attributes[1] = "to";
	attributes[2] = "length";

	long* values = FillAttributes(line,i,map,attributes);
	map.AddArc(values[0],values[1],values[2]);

	map.analizer = NULL;
}


void NodeAnalizer(char* line, int& i, Map& map)
{
	char** attributes = new char*[3];

	attributes[0] = "id";
	attributes[1] = "longitude";
	attributes[2] = "latitude";

	long* values = FillAttributes(line,i,map,attributes);
	map.AddNode(values[0],new Nod(values[0],values[1],values[2]));

	map.analizer = NULL;
}

void LineStart(char* line, int& i, Map& map)
{
	for(;i<strlen(line);i++)
	{
		if(line[i] == '<')
		{
			i++;
			map.analizer = StartTag;
			return;
		}
	}
	map.analizer = NULL;
}

void Map::AnalizeLine(char* line)
{
	bool addTag = true;
	analizer = LineStart;

	int n = strlen(line);
	int i=0;
	while(analizer)
	{
		analizer(line,i,*this);
	}
}

void Map::Read(char* fileName)
{
	queue<char*> tags;

	ifstream f(fileName);

	f.ignore(1000,'\n');
	f.ignore(1000,'\n');
	char *q = new char[100];

	while(!f.eof())
	{
		f.getline(q,100);
		AnalizeLine(q);
	}
	f.close();
}

int ToInt(string str)
{
	int number = 0;
	for(int i=0;i<str.size();i++)
	{
		number = number*10+(str[i]-'0');
	}
	return number;
}

void Map::CMarkupRead(char* fileName)
{
	CMarkup markMap;

	markMap.Load(fileName);

	markMap.FindElem(string("map"));
	markMap.IntoElem();
	markMap.FindElem(string("nodes"));
	markMap.IntoElem();

	while ( markMap.FindElem(string("node")))
	{
		int key = ToInt(markMap.GetAttrib("id"));
		int longitude = ToInt(markMap.GetAttrib("longitude"));
		int latitude = ToInt(markMap.GetAttrib("latitude"));
		AddNode(key,new Nod(key,longitude,latitude));
	}
	markMap.OutOfElem();
	markMap.FindElem(string("arcs"));
	markMap.IntoElem();
	while ( markMap.FindElem(string("arc")))
	{
		int from = ToInt(markMap.GetAttrib("from"));
		int to = ToInt(markMap.GetAttrib("to"));
		int length = ToInt(markMap.GetAttrib("length"));
		AddArc(from,to,length);
	}
}

void Map::Write(char* fileName)
{
	ofstream o(fileName);
	std::map<int,Nod*>::iterator it;

	for(it = nodes.begin();it != nodes.end();it++)
	{
		o<<*it->second<<endl;
	}
	o.close();
}

void Map::AddNode(int key,Nod* nod)
{
	nodes.insert(pair<int,Nod*>(key,nod));
}

void Map::AddArc(int from,int to,int length)
{
	nodes[from]->AddArc(nodes[to],length);
	//nodes[to]->AddArc(nodes[from],length);
}

map<int, Nod*>* Map::getMap() {
	return &nodes;
}	
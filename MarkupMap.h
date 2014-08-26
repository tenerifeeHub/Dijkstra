#pragma once

class MarkupMap
{
public:
	MarkupMap();
	~MarkupMap();

	void Read(char* fileName);
	void Write(char* fileName);
};

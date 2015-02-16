#ifndef XMLREAD_H_
#define XMLREAD_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

enum eNodeTyp
{
	Null,
	StartElement,
	EndElement,
	Element
};

class XMLRead
{
public:
	XMLRead(string Filename);
	~XMLRead();

	bool ReadLine();
	eNodeTyp GetNodeTyp();

	bool MoveToNextAttribute();
	
	string GetName();
	string GetValue();


private:
	fstream mFile;
	string mName;
	string mValue;
	eNodeTyp mTyp;
	map<string, string> mAttribute;
};

#endif

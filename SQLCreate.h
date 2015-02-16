#ifndef SQLCREATE_H_
#define SQLCREATE_H_

#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include "OSMRelation.h"

class SQLCreate
{
public:
	void SaveRelation(string FileName, OSMRelation * relation);
	void SaveRelation(string FileName, list<OSMRelation*> * relation);

private:
	string CreateNode(OSMNode * node);
	string CreateWay(OSMWay * way);
	string CreateRelation(OSMRelation * relation);
};

#endif

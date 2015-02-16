#ifndef SVGCREATE_H_
#define SVGCREATE_H_

#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include "OSMRelation.h"
#include "SVGItem.h"

class SVGCreate
{
public:
	SVGCreate();

	void SaveRelation(string FileName, OSMRelation * relation);
	void SaveRelation(string FileName, list<OSMRelation*> * relation);
	void SaveRelation(string FileName, list<OSMRelation*> * relation, list<SVGItem*> * SVGItems);

private:
	string mHeader;
	string mBottom;
	string mHeaderPoint;
	string mBottomPoint;
};

#endif

#include <algorithm>

#include "OSMLib.h"
#include "convert.h"
#include "OSMWay.h"

OSMWay::OSMWay(string line)
{
	vector<string> elements = split(line, cDivider);
	SetId(ConvertStringToInt(elements[0]));

	vector<string> Attribute = split(elements[1], cNextElement);
	vector<string> Nodes = split(elements[2], cNextElement);
	for(vector<string>::iterator it = Attribute.begin(); it != Attribute.end(); it++)
	{
		if(*it == "")
			break;
		vector<string> Att = split(*it, cElementDivider);
		if(Att.size() == 2)
			(*GetPAttributes())[Att[0]] = Att[1];
	}
	for(vector<string>::iterator it = Nodes.begin(); it != Nodes.end(); it++)
	{
		if(*it == "")
			break;
		GetPNodesId()->push_back(ConvertStringToInt(*it));
	}
}

list<OSMNode*> * OSMWay::GetPNodes()
{
	return & mNodes;
}

list<uint64_t> * OSMWay::GetPNodesId()
{
	return & mNodesId;
}

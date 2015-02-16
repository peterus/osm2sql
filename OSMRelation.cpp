#include <algorithm>

#include "OSMLib.h"
#include "convert.h"
#include "OSMRelation.h"

OSMRelation::OSMRelation(string line)
{
	vector<string> elements = split(line, cDivider);
	SetId(ConvertStringToInt(elements[0]));

	vector<string> Attribute = split(elements[1], cNextElement);
	vector<string> Ways = split(elements[2], cNextElement);
	vector<string> Nodes = split(elements[3], cNextElement);
	for(vector<string>::iterator it = Attribute.begin(); it != Attribute.end(); it++)
	{
		if(*it == "")
			break;
		vector<string> Att = split(*it, cElementDivider);
		if(Att.size() == 2)
			(*GetPAttributes())[Att[0]] = Att[1];
	}
	for(vector<string>::iterator it = Ways.begin(); it != Ways.end(); it++)
	{
		if(*it == "")
			break;
		GetPWaysId()->push_back(ConvertStringToInt(*it));
	}
	for(vector<string>::iterator it = Nodes.begin(); it != Nodes.end(); it++)
	{
		if(*it == "")
			break;
		GetPNodesId()->push_back(ConvertStringToInt(*it));
	}
}

list<OSMWay*> * OSMRelation::GetPWays()
{
	return & mWays;
}

list<OSMNode*> * OSMRelation::GetPNodes()
{
	return & mNodes;
}

list<uint64_t> * OSMRelation::GetPWaysId()
{
	return & mWaysId;
}

list<uint64_t> * OSMRelation::GetPNodesId()
{
	return & mNodesId;
}

string OSMRelation::GetName()
{
	map<string, string>::iterator it = GetPAttributes()->find("name");
	if (it != GetPAttributes()->end())
	{
		return it->second;
	}
	return ConvertIntToString(GetId());
}

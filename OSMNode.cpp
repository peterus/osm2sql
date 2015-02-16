#include <algorithm>

#include "OSMLib.h"
#include "convert.h"
#include "OSMNode.h"
#include "Point.h"

OSMNode::OSMNode()
{
	mLat = 0.0;
	mLon = 0.0;
}

OSMNode::OSMNode(string line)
{
	vector<string> elements = split(line, cDivider);
	SetId(ConvertStringToInt(elements[0]));
	SetLat(ConvertStringToDouble(elements[1]));
	SetLon(ConvertStringToDouble(elements[2]));

	vector<string> Attribute = split(elements[3], cNextElement);
	for(vector<string>::iterator it = Attribute.begin(); it != Attribute.end(); it++)
	{
		if(*it == "")
			break;
		vector<string> Att = split(*it, cElementDivider);
		if(Att.size() == 2)
			(*GetPAttributes())[Att[0]] = Att[1];
	}
}

OSMNode::OSMNode(Point oldPoint)
{
	mLat = oldPoint.GetLatitude();
	mLon = oldPoint.GetLongitude();
}

OSMNode::OSMNode(double Lat, double Lon)
{
	mLat = Lat;
	mLon = Lon;
}

void OSMNode::SetLat(double Lat)
{
	mLat = Lat;
}

double OSMNode::GetLat()
{
	return mLat;
}

void OSMNode::SetLon(double Lon)
{
	mLon = Lon;
}

double OSMNode::GetLon()
{
	return mLon;
}

string OSMNode::ToString()
{
	return "OSMNode";
}

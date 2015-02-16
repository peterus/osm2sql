#ifndef OSMNODE_H_
#define OSMNODE_H_

#include "OSMTopData.h"

class Point;

class OSMNode : public OSMTopData
{
public:
	OSMNode();
	OSMNode(string line);
	OSMNode(Point oldPoint);
	OSMNode(double Lat, double Lon);

	virtual void SetLat(double Lat);
	virtual double GetLat();

	virtual void SetLon(double Lon);
	virtual double GetLon();

	virtual string ToString();

private:
	double mLat;
	double mLon;
};

#endif

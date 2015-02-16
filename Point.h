#ifndef POINT_H_
#define POINT_H_

#include "OSMNode.h"

class Point
{
public:
	Point();
	Point(double Longitude, double Latitude);
	Point(OSMNode oldNode);

	void Set(double Longitude, double Latitude);

	double GetLongitude();
	double GetLatitude();
	bool IsSet();


private:
	double mLongitude;
	double mLatitude;
	bool mDefined;
};

#endif

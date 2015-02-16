#include "Point.h"

Point::Point()
{
	mDefined = false;
}

Point::Point(double Longitude, double Latitude)
{
	mLongitude = Longitude;
	mLatitude = Latitude;
	mDefined = true;
}


Point::Point(OSMNode oldNode)
{
	mLongitude = oldNode.GetLon();
	mLatitude = oldNode.GetLat();
	mDefined = true;
}

void Point::Set(double Longitude, double Latitude)
{
	mLongitude = Longitude;
	mLatitude = Latitude;
	mDefined = true;
}

double Point::GetLongitude()
{
	return mLongitude;
}

double Point::GetLatitude()
{
	return mLatitude;
}

bool Point::IsSet()
{
	return mDefined;
}

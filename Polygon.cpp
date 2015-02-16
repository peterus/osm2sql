#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Polygon.h"
#include "convert.h"

double Angle2D(double x1, double y1, double x2, double y2);

Polygon::Polygon()
{
}

void Polygon::Add(Point newPoint)
{
	mPoints.push_back(newPoint);
}

Point * Polygon::GetPoint(size_t position)
{
	if(position < mPoints.size())
	{
		return & mPoints[position];
	}
	return 0;
}

bool Polygon::PointInPolygon(Point p)
{
	bool found = false;
	size_t i, j;
	for(i = 0, j = mPoints.size() - 1; i < mPoints.size(); j = i++)
	{
		if ( ((mPoints[i].GetLatitude() > p.GetLatitude()) != (mPoints[j].GetLatitude() > p.GetLatitude())) &&
			(p.GetLongitude() < (mPoints[j].GetLongitude() - mPoints[i].GetLongitude()) * (p.GetLatitude() - mPoints[i].GetLatitude()) / (mPoints[j].GetLatitude() - mPoints[i].GetLatitude()) + mPoints[i].GetLongitude()) )
		{
			found = true;
		}
	}
	return found;
}

bool Polygon::RelationInPolygon(OSMRelation * rel)
{
	bool isIn = false;
	if(rel->GetPNodes()->size() != 0)
	{
		for (list<OSMNode*>::iterator it = rel->GetPNodes()->begin(); it != rel->GetPNodes()->end(); it++)
		{
			Point p = Point(**it);
			isIn |= this->PointInPolygon(p);
		}
	}
	else if(rel->GetPWays()->size() != 0)
	{
		for (list<OSMWay*>::iterator it = rel->GetPWays()->begin(); it != rel->GetPWays()->end(); it++)
		{
			if((*it)->GetPNodes()->size() != 0)
			{
				for (list<OSMNode*>::iterator itn = (*it)->GetPNodes()->begin(); itn != (*it)->GetPNodes()->begin(); itn++)
				{
					Point p = Point(**itn);
					isIn |= this->PointInPolygon(p);
				}
			}
		}
	}
	return isIn;
}

bool Polygon::PointInPolygonOther(Point p)
{
	double angle = 0.0;
	Point p1, p2;
	size_t n = mPoints.size();

	for (size_t i = 0; i < n; i++)
	{
		p1.Set(mPoints[i].GetLongitude() - p.GetLongitude(), mPoints[i].GetLatitude() - p.GetLatitude());
		p2.Set(mPoints[(i+1) % n].GetLongitude() - p.GetLongitude(), mPoints[(i+1) % n].GetLatitude() - p.GetLatitude());
		angle += Angle2D(p1.GetLatitude(), p1.GetLongitude(), p2.GetLatitude(), p2.GetLongitude());
	}

	if (abs(angle) < M_PI)
		return false;
	else
		return true;
}

bool Polygon::ReadPolygonFromFile(string Filename)
{
	ifstream ifile;
	ifile.open(Filename.c_str());

	uint64_t linec = 0;

	while(ifile.good())
	{
		string line;
		getline(ifile, line);
		if(line == "END")
		{
			break;
		}
		if(linec > 2)
		{
			Point p = GetPoint(line);
			if(p.IsSet())
			{
				this->Add(p);
			}
		}
		linec++;
	}

	return true;
}

Point Polygon::GetPoint(string line)
{
	bool lat = false;
	double dlat = 0.0;
	double dlon = 0.0;
	string tmp = "";
	for (uint64_t i = 0; i < line.size(); i++)
	{
		if(line[i] != ' ' && !lat)
		{
			tmp += line[i];
		}
		else if(line[i] == ' ' && !lat)
		{
			lat = true;
			//convert
			dlon = ConvertStringToDouble(tmp);
			tmp = "";
		}
		else if(line[i] != ' ' && lat)
		{
			tmp += line[i];
		}
	}
	dlat = ConvertStringToDouble(tmp);
	Point p;
	p.Set(dlon, dlat);
	return p;
}

double Angle2D(double x1, double y1, double x2, double y2)
{
	double dtheta,theta1,theta2;

	theta1 = atan2(y1,x1);
	theta2 = atan2(y2,x2);
	dtheta = theta2 - theta1;
	while (dtheta > M_PI)
		dtheta -= 2.0*M_PI;
	while (dtheta < -M_PI)
		dtheta += 2.0*M_PI;

	return(dtheta);
}

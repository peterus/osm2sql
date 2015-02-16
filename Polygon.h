#ifndef POLYGON_H_
#define POLYGON_H_

#include <vector>
#include "OSMRelation.h"
#include "Point.h"

class Polygon
{
public:
	Polygon();

	void Add(Point newPoint);

	Point * GetPoint(size_t position);
	bool PointInPolygon(Point p);
	bool RelationInPolygon(OSMRelation * rel);
	bool PointInPolygonOther(Point p);

	bool ReadPolygonFromFile(string Filename);

private:
	std::vector<Point> mPoints;
	Point GetPoint(string line);

};

#endif

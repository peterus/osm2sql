#ifndef CREATE_POLY_H_
#define CREATE_POLY_H_

#include <vector>
#include <list>
using namespace std;
#include "Polygon.h"
#include "OSMRelation.h"

vector<Polygon> * CreatePoly(list<OSMRelation * > * pRelations);

#endif
#ifndef SVGITEM_H_
#define SVGITEM_H_

#include <string>
using namespace std;
#include "OSMTopData.h"

class SVGItem
{
public:
	SVGItem(uint64_t Id, string Name, OSMTyp Typ, string Style);

	uint64_t GetId();
	string GetName();
	OSMTyp GetTyp();
	string GetStyle();

private:
	uint64_t mId;
	string mName;
	OSMTyp mTyp;
	string mStyle;
};

SVGItem * FindSVGItem(list<SVGItem*>::iterator begin, list<SVGItem*>::iterator end, uint64_t Id);

#endif

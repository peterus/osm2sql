#include "SVGItem.h"


SVGItem::SVGItem(uint64_t Id, string Name, OSMTyp Typ, string Style)
{
	mId = Id;
	mName = Name;
	mTyp = Typ;
	mStyle = Style;
}

uint64_t SVGItem::GetId()
{
	return mId;
}

string SVGItem::GetName()
{
	return mName;
}

OSMTyp SVGItem::GetTyp()
{
	return mTyp;
}

string SVGItem::GetStyle()
{
	return mStyle;
}

SVGItem * FindSVGItem(list<SVGItem*>::iterator begin, list<SVGItem*>::iterator end, uint64_t Id)
{
	for (; begin != end; begin++)
	{
		if ((*begin)->GetId() == Id)
		{
			return (*begin);
		}
	}
	return 0;
}

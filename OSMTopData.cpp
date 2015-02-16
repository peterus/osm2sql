#include "OSMTopData.h"

void OSMTopData::SetId(uint64_t Id)
{
	mId = Id;
}

uint64_t OSMTopData::GetId()
{
	return mId;
}

void OSMTopData::SetTyp(OSMTyp Typ)
{
	mTyp = Typ;
}

OSMTyp OSMTopData::GetTyp()
{
	return mTyp;
}

map<string, string> * OSMTopData::GetPAttributes()
{
	return & mAttributes;
}

string OSMTopData::ToString()
{
	return "OSMTopData";
}

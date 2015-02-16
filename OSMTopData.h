#ifndef OSMTOPDATA_H_
#define OSMTOPDATA_H_

#include <map>
#include <string>
#include <list>
using namespace std;

enum OSMTyp
{
	eNode,
	eWay,
	eRelation,
};

class OSMNode;
class OSMWay;
class OSMRelation;

class OSMTopData
{
public:
	OSMTopData()
	{
		mVisited = false;
	}

	virtual void SetId(uint64_t Id);
	virtual uint64_t GetId();

	virtual void SetTyp(OSMTyp Typ);
	virtual OSMTyp GetTyp();

	void Visit()
	{
		mVisited = true;
	}

	bool isVisit()
	{
		return mVisited;
	}

	virtual map<string, string> * GetPAttributes();

	virtual string ToString();

	virtual ~OSMTopData() { mAttributes.clear(); }

private:
	uint64_t mId;
	OSMTyp mTyp;
	map<string, string> mAttributes;
	bool mVisited;
};

#endif

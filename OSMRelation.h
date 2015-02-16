#ifndef OSRELATION_H_
#define OSRELATION_H_

#include "OSMWay.h"

class OSMRelation : public OSMTopData
{
public:
	OSMRelation(){}
	OSMRelation(string line);
	virtual list<OSMWay*> * GetPWays();
	virtual list<uint64_t> * GetPWaysId();

	virtual list<uint64_t> * GetPNodesId();
	virtual list<OSMNode*> * GetPNodes();

	virtual string GetName();

	virtual ~OSMRelation()
	{
		mWays.clear();
		mWaysId.clear();
		mNodes.clear();
		mNodesId.clear();
	}

private:
	list<OSMWay*> mWays;
	list<OSMNode*> mNodes;
	list<uint64_t> mWaysId;
	list<uint64_t> mNodesId;
};

#endif

#ifndef OSMWAY_H_
#define OSMWAY_H_

#include <list>
using namespace std;
#include "OSMNode.h"

class OSMWay : public OSMTopData
{
public:
	OSMWay(){}
	OSMWay(string line);
	virtual list<OSMNode*> * GetPNodes();
	virtual list<uint64_t> * GetPNodesId();

	virtual ~OSMWay()
	{
		mNodes.clear();
		mNodesId.clear();
	}

private:
	list<OSMNode*> mNodes;
	list<uint64_t> mNodesId;
};

#endif

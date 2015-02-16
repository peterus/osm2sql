#ifndef OSMREAD_H_
#define OSMREAD_H_

#include <list>
#include <vector>
#include <fstream>
using namespace std;
#include "OSMRelation.h"

class OSMRead
{
public:
	OSMRead();
	~OSMRead();

	void SetBufferRelation(string Filename);
	void SetBufferWay(string Filename);
	void SetBufferNode(string Filename);

	void AddRelationFilter(uint64_t Id);
	void AddRelationFilter(string k, string v);
	void AddWayFilter(uint64_t Id);
	void AddWayFilter(string k, string v);
	void AddNodeFilter(uint64_t Id);
	void AddNodeFilter(string k, string v);

	void Search();

//	list<OSMNode*> * GetNodes();
//	list<OSMWay*> * GetWays();
	list<OSMRelation*> * GetRelations();

private:
	list<OSMRelation*> mRelations;
	list<OSMWay*> mWays;
	list<OSMNode*> mNodes;

	vector<uint64_t> mRelationsId;
	vector<uint64_t> mWaysId;
	vector<uint64_t> mNodesId;

	map<string, string> mFilterRelations;
	map<string, string> mFilterWays;
	map<string, string> mFilterNodes;

	fstream mBufferRelation;
	fstream mBufferWay;
	fstream mBufferNode;

	void SearchRealtions();
	void SearchWays();
	void SearchNodes();

	void BringTogetherRelations();
	void BringTogetherWays();
};

#endif

#include <algorithm>

#include "OSMLib.h"
#include "XMLRead.h"
#include "OSMRead.h"
#include "OSMRelation.h"
#include "convert.h"
#include "InfoPrint.h"

OSMRead::OSMRead()
{
}

OSMRead::~OSMRead()
{
	for(list<OSMRelation*>::iterator it = mRelations.begin(); it != mRelations.end(); it++)
	{
		delete *it;
	}
	mRelations.clear();
	for (list<OSMWay*>::iterator it = mWays.begin(); it != mWays.end(); it++)
	{
		delete *it;
	}
	mWays.clear();
	for (list<OSMNode*>::iterator it = mNodes.begin(); it != mNodes.end(); it++)
	{
		delete *it;
	}
	mNodes.clear();
}

void OSMRead::SetBufferRelation(string Filename)
{
	mBufferRelation.open(Filename.c_str(), fstream::in);
}

void OSMRead::SetBufferWay(string Filename)
{
	mBufferWay.open(Filename.c_str(), fstream::in);
}

void OSMRead::SetBufferNode(string Filename)
{
	mBufferNode.open(Filename.c_str(), fstream::in);
}

void OSMRead::AddRelationFilter(uint64_t Id)
{
	vector<uint64_t>::iterator found = find(mRelationsId.begin(), mRelationsId.end(), Id);
	if(found == mRelationsId.end())
	{
		mRelationsId.push_back(Id);
	}
}

void OSMRead::AddRelationFilter(string k, string v)
{
	mFilterRelations[k] = v;
}

void OSMRead::AddWayFilter(uint64_t Id)
{
	vector<uint64_t>::iterator found = find(mWaysId.begin(), mWaysId.end(), Id);
	if(found == mWaysId.end())
	{
		mWaysId.push_back(Id);
	}
}

void OSMRead::AddWayFilter(string k, string v)
{
	mFilterWays[k] = v;
}

void OSMRead::AddNodeFilter(uint64_t Id)
{
	vector<uint64_t>::iterator found = find(mNodesId.begin(), mNodesId.end(), Id);
	if(found == mNodesId.end())
	{
		mNodesId.push_back(Id);
	}
}

void OSMRead::AddNodeFilter(string k, string v)
{
	mFilterNodes[k] = v;
}

void OSMRead::Search()
{
	if(!mBufferRelation.is_open() || !mBufferWay.is_open() || !mBufferNode.is_open())
	{
		cout << "Eine Datei konnte nicht geoeffnet werden!" << endl;
		return;
	}
	InfoPrint::Instance().PrintMsg("Search Start!");
	InfoPrint::Instance().PrintMsg("Sorting Relations...");
	sort(mRelationsId.begin(), mRelationsId.end());
	InfoPrint::Instance().PrintMsg("Start Searching Relations...");
	SearchRealtions();
	InfoPrint::Instance().PrintMsg("Sorting Ways...");
	sort(mWaysId.begin(), mWaysId.end());
	InfoPrint::Instance().PrintMsg("Start Searching Ways...");
	SearchWays();
	InfoPrint::Instance().PrintMsg("Sorting Nodes...");
	sort(mNodesId.begin(), mNodesId.end());
	InfoPrint::Instance().PrintMsg("Start Searching Nodes...");
	SearchNodes();
	InfoPrint::Instance().PrintMsg("Start Bringing Relations Together...");
	BringTogetherRelations();
	InfoPrint::Instance().PrintMsg("Start Bringing Ways Together...");
	BringTogetherWays();
	InfoPrint::Instance().PrintMsg("Search End!");
}


void OSMRead::SearchRealtions()
{
	string line;
	bool add = false;
	int size = mRelationsId.size();
	int sizem = 0;
	while (mBufferRelation.good())
	{
		getline(mBufferRelation, line);
		if (line == "")
		{
			continue;
		}
		OSMRelation * rel = new OSMRelation(line);
		bool found = binary_search(mRelationsId.begin(), mRelationsId.end(), rel->GetId());
		if (found)
		{
			mRelationsId.erase(find(mRelationsId.begin(), mRelationsId.end(), rel->GetId()));
		}
		if(!found)
		{
			for(map<string, string>::iterator it = mFilterRelations.begin(); it != mFilterRelations.end(); it++)
			{
				if(rel->GetPAttributes()->find(it->first) != rel->GetPAttributes()->end())
				{
					if(it->second == "*")
					{
						found = true;
					}
					else if((*rel->GetPAttributes())[it->first] == it->second)
					{
						found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				else
				{
					found = false;
					break;
				}
			}
		}
		if(found)
		{
			mRelations.push_back(rel);
			for(list<uint64_t>::iterator it = rel->GetPWaysId()->begin(); it != rel->GetPWaysId()->end(); it++)
			{
				mWaysId.push_back(*it);
			}
			for(list<uint64_t>::iterator it = rel->GetPNodesId()->begin(); it != rel->GetPNodesId()->end(); it++)
			{
				mNodesId.push_back(*it);
			}
			sizem++;
			InfoPrint::Instance().PrintMsg(ConvertIntToString(sizem) + " von " + ConvertIntToString(size) + " Relationen gefunden.");
		}
		else
		{
			delete rel;
		}
	}
}

void OSMRead::SearchWays()
{
	string line;
	bool add = false;
	int size = mWaysId.size();
	int sizem = 0;
	while (mBufferWay.good())
	{
		getline(mBufferWay, line);
		if (line == "")
		{
			continue;
		}
		OSMWay * way = new OSMWay(line);
		bool found = binary_search(mWaysId.begin(), mWaysId.end(), way->GetId());
		if (found)
		{
			mWaysId.erase(find(mWaysId.begin(), mWaysId.end(), way->GetId()));
		}
		if(!found)
		{
			for(map<string, string>::iterator it = mFilterWays.begin(); it != mFilterWays.end(); it++)
			{
				if(way->GetPAttributes()->find(it->first) != way->GetPAttributes()->end())
				{
					if(it->second == "*")
					{
						found = true;
						break;
					}
					else if((*way->GetPAttributes())[it->first] == it->second)
					{
						found = true;
						break;
					}
				}
			}
		}
		if(found)
		{
			mWays.push_back(way);
			for(list<uint64_t>::iterator it = way->GetPNodesId()->begin(); it != way->GetPNodesId()->end(); it++)
			{
				mNodesId.push_back(*it);
			}
			sizem++;
			InfoPrint::Instance().PrintMsg(ConvertIntToString(sizem) + " von " + ConvertIntToString(size) + " Ways gefunden.");
		}
		else
		{
			delete way;
		}
	}
}

void OSMRead::SearchNodes()
{
	string line;
	bool add = false;
	int size = mNodesId.size();
	int sizem = 0;
	while (mBufferNode.good())
	{
		getline(mBufferNode, line);
		if (line == "")
		{
			continue;
		}
		OSMNode * node = new OSMNode(line);
		bool found = binary_search(mNodesId.begin(), mNodesId.end(), node->GetId());
		if (found)
		{
			mNodesId.erase(find(mNodesId.begin(), mNodesId.end(), node->GetId()));
		}
		if(!found)
		{
			for(map<string, string>::iterator it = mFilterNodes.begin(); it != mFilterNodes.end(); it++)
			{
				if(node->GetPAttributes()->find(it->first) != node->GetPAttributes()->end())
				{
					if(it->second == "*")
					{
						found = true;
						break;
					}
					else if((*node->GetPAttributes())[it->first] == it->second)
					{
						found = true;
						break;
					}
				}
			}
		}
		if(found)
		{
			mNodes.push_back(node);
			sizem++;
			InfoPrint::Instance().PrintMsg(ConvertIntToString(sizem) + " von " + ConvertIntToString(size) + " Nodes gefunden.");
		}
		else
		{
			delete node;
		}
	}
}

/*
list<OSMNode*> * OSMRead::GetNodes()
{
	return & mNodes;
}

list<OSMWay*> * OSMRead::GetWays()
{
	return & mWays;
}
*/

list<OSMRelation*> * OSMRead::GetRelations()
{
	return & mRelations;
}

list<OSMNode*>::iterator findNode(list<OSMNode*>::iterator begin, list<OSMNode*>::iterator end, uint64_t id)
{
	while(begin != end)
	{
		if((*begin)->GetId() == id)
		{
			return begin;
		}
		begin++;
	}
	return end;
}

list<OSMWay*>::iterator findWay(list<OSMWay*>::iterator begin, list<OSMWay*>::iterator end, uint64_t id)
{
	while(begin != end)
	{
		if((*begin)->GetId() == id)
		{
			return begin;
		}
		begin++;
	}
	return end;
}

void OSMRead::BringTogetherRelations()
{
	for(list<OSMRelation*>::iterator rel = mRelations.begin(); rel != mRelations.end(); rel++)
	{
		for(list<uint64_t>::iterator way = (*rel)->GetPWaysId()->begin(); way != (*rel)->GetPWaysId()->end(); way++)
		{
			list<OSMWay*>::iterator it = findWay(mWays.begin(), mWays.end(), *way);
			if(it != mWays.end())
			{
				(*rel)->GetPWays()->push_back(*it);
			}
		}

		for(list<uint64_t>::iterator node = (*rel)->GetPNodesId()->begin(); node != (*rel)->GetPNodesId()->end(); node++)
		{
			list<OSMNode*>::iterator it = findNode(mNodes.begin(), mNodes.end(), *node);
			if(it != mNodes.end())
			{
				(*rel)->GetPNodes()->push_back(*it);
			}
		}

	}
}

void OSMRead::BringTogetherWays()
{
	for(list<OSMWay*>::iterator way = mWays.begin(); way != mWays.end(); way++)
	{
		for(list<uint64_t>::iterator node = (*way)->GetPNodesId()->begin(); node != (*way)->GetPNodesId()->end(); node++)
		{
			list<OSMNode*>::iterator it = findNode(mNodes.begin(), mNodes.end(), *node);
			if(it != mNodes.end())
			{
				(*way)->GetPNodes()->push_back(*it);
			}
		}

	}
}

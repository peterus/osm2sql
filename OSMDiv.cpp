#include "OSMLib.h"
#include "OSMDiv.h"
#include "convert.h"

OSMDiv::OSMDiv(string Filename)
	: mRead(Filename)
{
	mReadFile = Filename;
	mRelationFile = "";
	mWayFile = "";
	mNodeFile = "";
	mCurrent = 0;
}

OSMDiv::~OSMDiv()
{
	if (mRelationFileS.is_open())
	{
		mRelationFileS.close();
	}
	if (mRelationFileSQL.is_open())
	{
		mRelationFileSQL.close();
	}
	if (mWayFileS.is_open())
	{
		mWayFileS.close();
	}
	if (mWayFileSQL.is_open())
	{
		mWayFileSQL.close();
	}
	if (mNodeFileS.is_open())
	{
		mNodeFileS.close();
	}
	if (mNodeFileSQL.is_open())
	{
		mNodeFileSQL.close();
	}
	if (mReadFileS.is_open())
	{
		mReadFileS.close();
	}
}

void OSMDiv::SetRelationFile(string Filename)
{
	mRelationFile = Filename;
	mRelationFileS.open(mRelationFile.c_str(), fstream::out);
}

void OSMDiv::SetRelationSQLFile(string Filename)
{
	mRelationFileSQL.open(string(Filename + ".sql").c_str(), fstream::out);
}

void OSMDiv::SetWayFile(string Filename)
{
	mWayFile = Filename;
	mWayFileS.open(mWayFile.c_str(), fstream::out);
}

void OSMDiv::SetWaySQLFile(string Filename)
{
	mWayFileSQL.open(string(Filename + ".sql").c_str(), fstream::out);
}

void OSMDiv::SetNodeFile(string Filename)
{
	mNodeFile = Filename;
	mNodeFileS.open(mNodeFile.c_str(), fstream::out);
}

void OSMDiv::SetNodeSQLFile(string Filename)
{
	mNodeFileSQL.open(string(Filename + ".sql").c_str(), fstream::out);
}

void OSMDiv::Div()
{
	while(mRead.ReadLine())
	{
		if(mRead.GetNodeTyp() == StartElement || mRead.GetNodeTyp() == Element)
		{
			if(mRead.GetName() == "node")
			{
				WorkNode();
			}
			else if(mRead.GetName() == "way")
			{
				WorkWay();
			}
			else if(mRead.GetName() == "relation")
			{
				WorkRelation();
			}
			else if(mRead.GetName() == "tag")
			{
				WorkTag();
			}
			else if(mRead.GetName() == "nd")
			{
				WorkND();
			}
			else if(mRead.GetName() == "member")
			{
				WorkMember();
			}
			else
			{
				cout << "Kenn ich nicht: " << mRead.GetName() << endl;
			}
		}
		else if(mRead.GetNodeTyp() == EndElement)
		{
			if (mCurrent != 0)
			{
				if (mCurrent->GetTyp() == eNode)
				{
					SaveNode();
				}
				else if (mCurrent->GetTyp() == eWay)
				{
					SaveWay();
				}
				else if (mCurrent->GetTyp() == eRelation)
				{
					SaveRelation();
				}
				delete mCurrent;
				mCurrent = 0;
			}
			return;
		}
	}
}

void OSMDiv::WorkNode()
{
	if(mNodeFileS.is_open() || mNodeFileSQL.is_open())
	{
		mCurrent = new OSMNode();
		mCurrent->SetTyp(eNode);
		while(mRead.MoveToNextAttribute())
		{
			if(mRead.GetName() == "id")
			{
				mCurrent->SetId(ConvertStringToInt(mRead.GetValue()));
			}
			else if(mRead.GetName() == "lat")
			{
				((OSMNode*)mCurrent)->SetLat(ConvertStringToDouble(mRead.GetValue()));
			}
			else if(mRead.GetName() == "lon")
			{
				((OSMNode*)mCurrent)->SetLon(ConvertStringToDouble(mRead.GetValue()));
			}
		}
	}
	if(mRead.GetNodeTyp() == StartElement)
	{
		this->Div();
	}
	else
	{
		SaveNode();
		delete mCurrent;
		mCurrent = 0;
	}
}

void OSMDiv::WorkWay()
{
	if(mWayFileS.is_open() || mWayFileSQL.is_open())
	{
		mCurrent = new OSMWay();
		mCurrent->SetTyp(eWay);
		while(mRead.MoveToNextAttribute())
		{
			if(mRead.GetName() == "id")
			{
				mCurrent->SetId(ConvertStringToInt(mRead.GetValue()));
			}
		}
	}
	if(mRead.GetNodeTyp() == StartElement)
	{
		this->Div();
	}
	else
	{
		SaveWay();
		delete mCurrent;
		mCurrent = 0;
	}
}

void OSMDiv::WorkRelation()
{
	if(mRelationFileS.is_open() || mRelationFileSQL.is_open())
	{
		mCurrent = new OSMRelation();
		mCurrent->SetTyp(eRelation);
		while(mRead.MoveToNextAttribute())
		{
			if(mRead.GetName() == "id")
			{
				mCurrent->SetId(ConvertStringToInt(mRead.GetValue()));
			}
		}
	}
	if(mRead.GetNodeTyp() == StartElement)
	{
		this->Div();
	}
	else
	{
		SaveRelation();
		delete mCurrent;
		mCurrent = 0;
	}
}

void OSMDiv::WorkTag()
{
	if(mCurrent != 0)
	{
		string k, v;
		while(mRead.MoveToNextAttribute())
		{
			if(mRead.GetName() == "k")
			{
				k = mRead.GetValue();
			}
			else if(mRead.GetName() == "v")
			{
				v = mRead.GetValue();
			}
		}
		(*mCurrent->GetPAttributes())[k] = v;
	}
}

void OSMDiv::WorkND()
{
	if(mWayFileS.is_open() || mRelationFileSQL.is_open())
	{
		uint64_t id = 0;
		while(mRead.MoveToNextAttribute())
		{
			if(mRead.GetName() == "ref")
				id = ConvertStringToInt(mRead.GetValue());
		}
		if(id != 0)
			((OSMWay*)mCurrent)->GetPNodesId()->push_back(id);
	}
}

void OSMDiv::WorkMember()
{
	if(mRelationFileS.is_open() || mRelationFileSQL.is_open())
	{
		uint64_t id = 0;
		string typ = "";
		while(mRead.MoveToNextAttribute())
		{
			if(mRead.GetName() == "ref")
				id = ConvertStringToInt(mRead.GetValue());
			else if(mRead.GetName() == "type")
				typ = mRead.GetValue();
		}
		if(id != 0 && typ == "way")
			((OSMRelation*)mCurrent)->GetPWaysId()->push_back(id);
		else if(id != 0 && typ == "node")
			((OSMRelation*)mCurrent)->GetPNodesId()->push_back(id);
	}
}

void OSMDiv::SaveNode()
{
	if(mNodeFileS.is_open())
	{
		mNodeFileS << mCurrent->GetId() << cDivider << ((OSMNode*)mCurrent)->GetLat() << cDivider << ((OSMNode*)mCurrent)->GetLon() << cDivider;
		for (map<string, string>::iterator it = mCurrent->GetPAttributes()->begin(); it != mCurrent->GetPAttributes()->end(); )
		{
			mNodeFileS << it->first << cElementDivider << it->second;
			it++;
			if(it != mCurrent->GetPAttributes()->end())
			{
				mNodeFileS << cNextElement;
			}
		}
		mNodeFileS << endl;
	}
	SaveSQLNode();
}

void OSMDiv::SaveSQLNode()
{
	if(mNodeFileSQL.is_open())
	{
		mNodeFileSQL << "INSERT IGNORE INTO `Node` SET `idNode` = " << mCurrent->GetId() <<
			", `Lat` = " << ((OSMNode*)mCurrent)->GetLat() <<
			", `Lon` = " << ((OSMNode*)mCurrent)->GetLon() << ";" << endl;
	}
}

void OSMDiv::SaveWay()
{
	if(mWayFileS.is_open())
	{
		mWayFileS << mCurrent->GetId() << cDivider;
		for (map<string, string>::iterator it = mCurrent->GetPAttributes()->begin(); it != mCurrent->GetPAttributes()->end(); )
		{
			mWayFileS << it->first << cElementDivider << it->second;
			it++;
			if(it != mCurrent->GetPAttributes()->end())
			{
				mWayFileS << cNextElement;
			}
		}
		mWayFileS << cDivider;
		for(list<uint64_t>::iterator it = ((OSMWay*)mCurrent)->GetPNodesId()->begin(); it != ((OSMWay*)mCurrent)->GetPNodesId()->end(); )
		{
			mWayFileS << *it;
			it++;
			if(it != ((OSMWay*)mCurrent)->GetPNodesId()->end())
			{
				mWayFileS << cNextElement;
			}
		}
		mWayFileS << endl;
	}
	SaveSQLWay();
}

void OSMDiv::SaveSQLWay()
{
	if(mWayFileSQL.is_open())
	{
		mWayFileSQL << "INSERT IGNORE INTO `Way` SET `idWay` = " << mCurrent->GetId() << ";" << endl;
		int i = 1;
		for(list<uint64_t>::iterator it = ((OSMWay*)mCurrent)->GetPNodesId()->begin(); it != ((OSMWay*)mCurrent)->GetPNodesId()->end(); it++)
		{
			mWayFileSQL << "INSERT IGNORE INTO `Way_has_Node` SET `Way_idWay` = " << mCurrent->GetId() << ", `Node_idNode` = " << *it << ", `Way_has_Node`.`order` = " << i << ";" << endl;
			i++;
		}
	}
}

void OSMDiv::SaveRelation()
{
	if(mRelationFileS.is_open())
	{
		mRelationFileS << mCurrent->GetId() << cDivider;
		for (map<string, string>::iterator it = mCurrent->GetPAttributes()->begin(); it != mCurrent->GetPAttributes()->end(); )
		{
			mRelationFileS << it->first << cElementDivider << it->second;
			it++;
			if(it != mCurrent->GetPAttributes()->end())
			{
				mRelationFileS << cNextElement;
			}
		}
		mRelationFileS << cDivider;
		for(list<uint64_t>::iterator it = ((OSMRelation*)mCurrent)->GetPWaysId()->begin(); it != ((OSMRelation*)mCurrent)->GetPWaysId()->end(); )
		{
			mRelationFileS << *it;
			it++;
			if(it != ((OSMRelation*)mCurrent)->GetPWaysId()->end())
			{
				mRelationFileS << cNextElement;
			}
		}
		mRelationFileS << cDivider;
		for(list<uint64_t>::iterator it = ((OSMRelation*)mCurrent)->GetPNodesId()->begin(); it != ((OSMRelation*)mCurrent)->GetPNodesId()->end(); )
		{
			mRelationFileS << *it;
			it++;
			if(it != ((OSMRelation*)mCurrent)->GetPNodesId()->end())
			{
				mRelationFileS << cNextElement;
			}
		}
		mRelationFileS << endl;
	}
	SaveSQLRelation();
}

void OSMDiv::SaveSQLRelation()
{
	if(mRelationFileSQL.is_open())
	{
		string name = "";
		for (map<string, string>::iterator it = mCurrent->GetPAttributes()->begin(); it != mCurrent->GetPAttributes()->end(); it++)
		{
			if(it->first == "name")
			{
				name = it->second;
			}
		}
		if (name != "")
		{
			mRelationFileSQL << "INSERT IGNORE INTO `Relation` SET `idRelation` = " << mCurrent->GetId() << ", `Name` = \"" << name << "\";" << endl;
		} 
		else
		{
			mRelationFileSQL << "INSERT IGNORE INTO `Relation` SET `idRelation` = " << mCurrent->GetId() << ";" << endl;
		}
		for(list<uint64_t>::iterator it = ((OSMRelation*)mCurrent)->GetPWaysId()->begin(); it != ((OSMRelation*)mCurrent)->GetPWaysId()->end(); it++)
		{
			mRelationFileSQL << "INSERT IGNORE INTO `Relation_has_Way` SET `Relation_idRelation` = " << mCurrent->GetId() << ", `Way_idWay` = " << *it << ";" << endl;
		}
	}
}


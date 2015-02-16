#ifndef OSMDIV_H_
#define OSMDIV_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "XMLRead.h"
#include "OSMRelation.h"

class OSMDiv
{
public:
	OSMDiv(string Filename);
	~OSMDiv();

	void SetRelationFile(string Filename);
	void SetWayFile(string Filename);
	void SetNodeFile(string Filename);

	void SetRelationSQLFile(string Filename);
	void SetWaySQLFile(string Filename);
	void SetNodeSQLFile(string Filename);

	void Div();

private:
	XMLRead mRead;
	string mReadFile;
	fstream mReadFileS;
	string mRelationFile;
	fstream mRelationFileS;
	fstream mRelationFileSQL;
	string mWayFile;
	fstream mWayFileS;
	fstream mWayFileSQL;
	string mNodeFile;
	fstream mNodeFileS;
	fstream mNodeFileSQL;

	void WorkNode();
	void WorkWay();
	void WorkRelation();
	void WorkTag();
	void WorkND();
	void WorkMember();

	OSMTopData * mCurrent;

	void SaveNode();
	void SaveWay();
	void SaveRelation();

	void SaveSQLNode();
	void SaveSQLWay();
	void SaveSQLRelation();
};

#endif

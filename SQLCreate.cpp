#include "SQLCreate.h"
#include "convert.h"

void SQLCreate::SaveRelation(string FileName, OSMRelation * relation)
{

}

void SQLCreate::SaveRelation(string FileName, list<OSMRelation*> * relation)
{

}

string SQLCreate::CreateNode(OSMNode * node)
{
	string sql = "INSERT IGNORE INTO `Node` SET `idNode` = '" + ConvertIntToString(node->GetId()) +
		"', `Lat` = '" + ConvertDoubleToString(node->GetLat()) +
		"', `Lon` = '" + ConvertDoubleToString(node->GetLon()) +
		"';";
	return sql;
}

string SQLCreate::CreateWay(OSMWay * way)
{
	string sql = "INSERT IGNORE INTO `Way` SET `idWay` = '" + ConvertIntToString(way->GetId()) +
		"';";
	return sql;
}

string SQLCreate::CreateRelation(OSMRelation * relation)
{
	string sql = "INSERT IGNORE INTO `Relation` SET `idRelation` = '" + ConvertIntToString(relation->GetId()) +
		"', `Name` = '" + relation->GetName() +
		"';";
	return sql;
}

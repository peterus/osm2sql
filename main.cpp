#include <string>

using namespace std;

#include "OSMLib.h"

const string buffer_node = "node";
const string buffer_way = "way";
const string buffer_relation = "relation";

int main(int argc, char ** arg)
{
	if (argc < 2)
	{
		cout << "you must define a input file!" << endl;
		return -1;
	}
	cout << "File: " << arg[1] << endl;
	OSMDiv Div(arg[1]);

	InfoPrint::Instance().StartTimer();

	Div.SetNodeSQLFile(buffer_node);
	Div.SetWaySQLFile(buffer_way);
	Div.SetRelationSQLFile(buffer_relation);


	InfoPrint::Instance().PrintMsg("Begin of dividing...");

	Div.Div();

	InfoPrint::Instance().PrintMsg("Ende");
	InfoPrint::Instance().PrintMsg("Nodes in " + buffer_node);
	InfoPrint::Instance().PrintMsg("Ways in " + buffer_way);
	InfoPrint::Instance().PrintMsg("Relations in " + buffer_relation);

	return 0;
}

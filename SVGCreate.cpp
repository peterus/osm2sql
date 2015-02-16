#include "SVGCreate.h"
#include "convert.h"
#include "SVGItem.h"

SVGCreate::SVGCreate()
{
	mHeader = "<?xml version=\"1.0\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\n<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n\n";
	mBottom = "\n</svg>";
	mHeaderPoint = "<polyline points=\"";
	mBottomPoint = "\"\n  style=\"stroke:black;stroke-width:0.5;fill:none\" />\n";
}


void SVGCreate::SaveRelation(string FileName, OSMRelation * relation)
{
	ofstream File;
	File.open(FileName.c_str());
	File << mHeader;
	string points;
	for (list<OSMWay*>::iterator way = relation->GetPWays()->begin(); way != relation->GetPWays()->end(); way++)
	{
		points = "";
		for(list<OSMNode*>::iterator node = (*way)->GetPNodes()->begin(); node != (*way)->GetPNodes()->end(); node++)
		{
			points += ConvertDoubleToString((*node)->GetLat() * 500.0) + "," + ConvertDoubleToString((*node)->GetLon() * 500.0) + " ";
		}
		File << mHeaderPoint << points << mBottomPoint;
	}
	File << mBottom;
	File.close();
}

void SVGCreate::SaveRelation(string FileName, list<OSMRelation*> * relation)
{
	ofstream File;
	File.open(FileName.c_str());
	File << mHeader;
	string points;
	for (list<OSMRelation*>::iterator rel = relation->begin(); rel != relation->end(); rel++)
	{
		for (list<OSMWay*>::iterator way = (*rel)->GetPWays()->begin(); way != (*rel)->GetPWays()->end(); way++)
		{
			points = "";
			for(list<OSMNode*>::iterator node = (*way)->GetPNodes()->begin(); node != (*way)->GetPNodes()->end(); node++)
			{
				points += ConvertDoubleToString((*node)->GetLat() * 500.0) + "," + ConvertDoubleToString((*node)->GetLon() * 500.0) + " ";
			}
			File << mHeaderPoint << points << mBottomPoint;
		}
	}
	File << mBottom;
	File.close();
}

void SVGCreate::SaveRelation(string FileName, list<OSMRelation*> * relation, list<SVGItem*> * SVGItems)
{
	ofstream File;
	File.open(FileName.c_str());
	File << mHeader;
	string points;
	for (list<OSMRelation*>::iterator rel = relation->begin(); rel != relation->end(); rel++)
	{
		SVGItem * Item = FindSVGItem(SVGItems->begin(), SVGItems->end(), (*rel)->GetId());
		if(Item != 0)
		{
			File << "<g>" << endl << "<path d=\"";
			points = "";
			for (list<OSMWay*>::iterator way = (*rel)->GetPWays()->begin(); way != (*rel)->GetPWays()->end(); way++)
			{
				/*for(list<OSMNode*>::iterator node = (*way)->GetPNodes()->begin(); node != (*way)->GetPNodes()->end(); node++)
				{
					if(way == (*rel)->GetPWays()->begin() && node == (*way)->GetPNodes()->begin())
					{
						points += "M " + ConvertDoubleToString((*node)->GetLat() * 100.0) + " " + ConvertDoubleToString((*node)-> GetLon() * 100.0) + " ";
					}
					else
					{
						points += "L " + ConvertDoubleToString((*node)->GetLat() * 100.0) + " " + ConvertDoubleToString((*node)-> GetLon() * 100.0) + " ";
					}
				}
				*/
				
				OSMNode * nodebegin = *(*way)->GetPNodes()->begin();
				OSMNode * nodeend = *(*way)->GetPNodes()->rbegin();

				if(way == (*rel)->GetPWays()->begin())
				{
					points += "M " + ConvertDoubleToString(nodebegin->GetLat() * 100.0) + " " + ConvertDoubleToString(nodebegin->GetLon() * 100.0) + " ";
				}
				else
				{
					points += "L " + ConvertDoubleToString(nodebegin->GetLat() * 100.0) + " " + ConvertDoubleToString(nodebegin->GetLon() * 100.0) + " ";
				}
				points += "L " + ConvertDoubleToString(nodeend->GetLat() * 100.0) + " " + ConvertDoubleToString(nodeend-> GetLon() * 100.0) + " ";
				
			}
			File << points;
			File << "\"" << endl << "  style=\"" << Item->GetStyle() << "\" />" << endl;
			File << "</g>" << endl;
		}
	}
	File << mBottom;
	File.close();
}

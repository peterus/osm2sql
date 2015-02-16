#ifndef OSMLIB_H_
#define OSMLIB_H_

#include "convert.h"
#include "InfoPrint.h"
#include "OSMDiv.h"
#include "OSMNode.h"
#include "OSMRead.h"
#include "OSMRelation.h"
#include "OSMTopData.h"
#include "OSMWay.h"
#include "Point.h"
#include "Polygon.h"
#include "Singleton.h"
#include "SVGCreate.h"
#include "SVGItem.h"
#include "XMLRead.h"

const char cDivider[] = {0x01, 0};
const char cElementDivider[] = {0x02, 0};
const char cNextElement[] = {0x03, 0};

#endif
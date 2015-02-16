#ifndef INFOPRINT_H_
#define INFOPRINT_H_

#include <time.h>
#include <string>
using namespace std;
#include "Singleton.h"

class InfoPrint : public CSingleton<InfoPrint>
{
public:
	void StartTimer();
	void PrintMsg(string str);

private:
	time_t mTime;
};

#endif

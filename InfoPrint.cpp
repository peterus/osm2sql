#include <iostream>
#include <iomanip>
#include "InfoPrint.h"

void InfoPrint::StartTimer()
{
	time(&mTime);
}

double modulus(double a, double b)
{
	uint64_t result = static_cast<uint64_t>( a / b );
	return a - static_cast<double>( result ) * b;
}

void InfoPrint::PrintMsg(string str)
{
	time_t end;
	time(&end);
	double dif = difftime(end, mTime);
	int h = (int)dif / 60;
	int min = (int)dif % 60;
	cout << "Time: " << setw(2) << setfill('0') << h << ":" << setw(2) << setfill('0') << min << ", Msg: " << str << endl;
}

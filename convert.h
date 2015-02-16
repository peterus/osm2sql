#ifndef CONVERT_H_
#define CONVERT_H_

#include <string>
#include <vector>
#include <cstdint>
using namespace std;

uint64_t ConvertStringToInt(string str);
double ConvertStringToDouble(string str);
string ConvertIntToString(uint64_t i);
string ConvertDoubleToString(double i);
vector<string> split(const string & s, const string & delim, const bool keep_empty = true);

#endif

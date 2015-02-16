#include <sstream>
#include <algorithm>
#include <iterator>

#include "convert.h"

uint64_t ConvertStringToInt(string str)
{
	std::stringstream sstr(str);
	uint64_t Zahl;
	sstr >> Zahl;
	return Zahl;
}

double ConvertStringToDouble(string str)
{
	std::stringstream sstr(str);
	double Zahl;
	sstr >> Zahl;
	return Zahl;
}

string ConvertIntToString(uint64_t i)
{
	std::stringstream out;
	out << i;
	return out.str();
}

string ConvertDoubleToString(double i)
{
	std::stringstream out;
	out << i;
	return out.str();
}

vector<string> split(const string & s, const string & delim, const bool keep_empty)
{
	vector<string> result;
	if (delim.empty())
	{
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true)
	{
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty())
		{
			result.push_back(temp);
		}
		if (subend == s.end())
		{
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}



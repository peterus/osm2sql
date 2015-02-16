#ifndef SINGLETON_H_
#define SINGLETON_H_

template<typename T>
class CSingleton
{
public:
	static T & Instance()
	{
		static T me;
		return me;
	}
};

#endif

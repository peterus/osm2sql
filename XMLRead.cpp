#include "XMLRead.h"

enum eFileInfo
{
	FileSpace,
	FileName,
	FileOther,
	FileEndLine,
	FileEndNode,
};

enum eAttribute
{
	AttName,
	AttValue,
};

XMLRead::XMLRead(string Filename)
{
	mFile.open(Filename.c_str(), fstream::in);
	if (!mFile.is_open())
	{
		cout << "ERROR opening Inputfile!" << endl;
	}
	mName = "";
	mTyp = Null;
}

XMLRead::~XMLRead()
{
	mFile.close();
}

bool XMLRead::ReadLine()
{
	mName = "";
	mTyp = Null;

	string line;
	getline(mFile, line);

	eFileInfo info;
	info = FileSpace;

	eAttribute attribute;
	attribute = AttName;
	string attributeName = "";
	string attributeValue = "";
	mAttribute.clear();

	for(uint64_t i = 0; i < line.length(); i++)
	{
		if(info == FileName && line[i] != ' ')
		{
			if(line[i] != '>')
				mName += line[i];
		}
		else if(info == FileName && line[i] == ' ')
		{
			info = FileOther;
		}

		if(info == FileSpace && line[i] == '<' && line[i+1] == '/')
		{
			info = FileName;
			mTyp = EndElement;
			i++;
		}
		else if(info == FileSpace && line[i] == '<')
		{
			info = FileName;
			mTyp = Element;
		}

		if((info == FileOther || info == FileName) && line[i] == '/' && line[i+1] == '>')
		{
			info = FileEndNode;
		}
		else if((info == FileOther || info == FileName) && line[i] == '>')
		{
			info = FileEndLine;
			if(mTyp == Element)
				mTyp = StartElement;
		}
		else if(info == FileOther)
		{
			if(attribute == AttName)
			{
				if(line[i] == '=' && line[i+1] == '\"')
				{
					attribute = AttValue;
					i++;
				}
				else if(line[i] != ' ')
					attributeName += line[i];
			}
			else if(attribute == AttValue)
			{
				if(line[i] == '\"')
				{
					mAttribute[attributeName] = attributeValue;
					attribute = AttName;
					attributeName = "";
					attributeValue = "";
				}
				else
				{
					attributeValue += line[i];
				}
			}
		}
	}
	return mFile.good();
}

eNodeTyp XMLRead::GetNodeTyp()
{
	return mTyp;
}

bool XMLRead::MoveToNextAttribute()
{
	if(mAttribute.size() > 0)
	{
		mName = mAttribute.begin()->first;
		mValue = mAttribute.begin()->second;
		mAttribute.erase(mAttribute.begin());
		return true;
	}
	return false;
}

string XMLRead::GetName()
{
	return mName;
}

string XMLRead::GetValue()
{
	return mValue;
}


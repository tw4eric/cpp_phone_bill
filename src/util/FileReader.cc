#include <iostream>
#include "util/FileReader.hh"

using namespace std;

namespace util
{
	FileReader::FileReader(const string fileName)
	: fileNameM(fileName)
	{

	}

	FileReader::FileReader(const FileReader& fileReader)
	: fileNameM(fileReader.fileNameM)
	{

	}

	FileReader::~FileReader()
	{

	}

	bool FileReader::open()
	{
		fileStreamM.open (fileNameM.c_str(), ifstream::in);
		if(!fileStreamM.good())
		{
			fileStreamM.close();
			cerr << "Unable to open file: " << fileNameM << endl;
			return false;
		}
		return true;
	}

	string FileReader::getLine()
	{
		if(!fileStreamM.eof())
		{
			string line;
			getline(fileStreamM, line);
			return line;
		}

		return "";
	}

	void FileReader::close()
	{
		if(fileStreamM.is_open())
		{
			fileStreamM.close();
		}
	}
};

/*
 * FileReader.hh
 *
 */

#ifndef FILEREADER_HH_
#define FILEREADER_HH_

#include <string>
#include <fstream>

namespace util
{
	class FileReader
	{
	public:
		FileReader(const std::string fileName);
		FileReader(const FileReader& fileReader);
		virtual ~FileReader();
		virtual bool open();
		virtual std::string getLine();
		virtual void close();

	private:
		std::string fileNameM;
		std::ifstream fileStreamM;
	};

};

#endif /* FILEREADER_HH_ */

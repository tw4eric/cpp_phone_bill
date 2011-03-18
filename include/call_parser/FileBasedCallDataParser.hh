#ifndef FILEBASEDCALLDATAPARSER_HH_
#define FILEBASEDCALLDATAPARSER_HH_

#include <string>
using namespace std;

#include "util/FileReader.hh"

#include "CallDataParser.hh"

namespace CallParser {

	class FileBasedCallDataParser : public CallDataParser {

	    public:
/*
<<<<<<< Updated upstream
		FileBasedCallDataParser(string fileName);
=======
*/
		  FileBasedCallDataParser(util::FileReader* fileReader);
		  FileBasedCallDataParser(const FileBasedCallDataParser& fileBasedCallDataParser);
//>>>>>>> Stashed changes
	      ~FileBasedCallDataParser();
	       virtual list<CallRecord*>* parseRecords();
		private:
	       CallRecord* toCallRecord(string line);

	       util::FileReader* fileReaderM;
	};
}


#endif /* FILEBASEDCALLDATAPARSER_HH_ */

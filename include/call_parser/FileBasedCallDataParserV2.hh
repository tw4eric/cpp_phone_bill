#ifndef FILEBASEDCALLDATAPARSERV2_HH_
#define FILEBASEDCALLDATAPARSERV2_HH_

#include <string>
using namespace std;

#include "CallDataParser.hh"

namespace CallParser {

	class FileBasedCallDataParserV2 : public CallDataParser {

	    public:
	      FileBasedCallDataParserV2(string fileName);
	      ~FileBasedCallDataParserV2();
	       virtual list<CallRecord*>* parseRecords();
		private:
	       CallRecord* toCallRecord(string line);

	       string _fileName;
	};
}


#endif /* FILEBASEDCALLDATAPARSER_HH_ */

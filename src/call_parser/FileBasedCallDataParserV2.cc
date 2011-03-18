#include "call_parser/FileBasedCallDataParserV2.hh"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>

#include "util/FileReader.hh"

using namespace std;
using namespace boost::xpressive;

namespace CallParser {

FileBasedCallDataParserV2::FileBasedCallDataParserV2(string fileName) :
	_fileName(fileName) {
}

FileBasedCallDataParserV2::~FileBasedCallDataParserV2() {
}

list<CallRecord*>* FileBasedCallDataParserV2::parseRecords() {
	list<CallRecord*>* callRecordList = new list<CallRecord*> ;

	util::FileReader fileReader(_fileName);

	if (!fileReader.open()) {
		return callRecordList;
	}

	string line;
    line = fileReader.getLine();

	if (strcmp(line.c_str(), "#v2")==0)
	{
		while ((line = fileReader.getLine()) != "")
		{
			CallRecord* callRec = toCallRecord(line);
			if (callRec != NULL)
			{
					callRecordList->push_back(callRec);
			}
		}
	}

	fileReader.close();

	return callRecordList;
}

CallRecord* FileBasedCallDataParserV2::toCallRecord(string line) {
	sregex rex = sregex::compile("([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)");
	smatch what;
	CallRecord* callRec = NULL;

	if (regex_match(line, what, rex)) {
		try {

            callRec=new CallRecord(what[2],CallType::toCallType(what[3]),
                             boost::lexical_cast<int>(what[4]),what[5],what[1]);
			return callRec;
		} catch (...) {
			cerr << "Invalid Record Found: " << line << endl;
		}
	}
	return NULL;
}

}

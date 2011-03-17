#include "call_parser/FileBasedCallDataParserV2.hh"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::xpressive;

namespace CallParser {

FileBasedCallDataParserV2::FileBasedCallDataParserV2(string fileName) :
	_fileName(fileName) {
}

FileBasedCallDataParserV2::~FileBasedCallDataParserV2() {
}

list<CallRecord*>* FileBasedCallDataParserV2::parseRecords() {
	list<CallRecord*>* callRecordList = NULL;

	ifstream recFile(_fileName.c_str());

	if (!recFile) {
		cerr << "Unable to open file: " << _fileName << endl;
		return callRecordList;
	}

	string line;
	std::getline(recFile, line);

	if (strcmp(line.c_str(), "#V2")) {
		while (std::getline(recFile, line)) {
			CallRecord* callRec = toCallRecord(line);
			if (callRec != NULL) {
				callRecordList->push_back(callRec);
			}
		}
	}

	recFile.close();

	return callRecordList;
}

CallRecord* FileBasedCallDataParserV2::toCallRecord(string line) {
	sregex rex = sregex::compile("([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)");
	smatch what;

	CallRecord* callRec = NULL;

	if (regex_match(line, what, rex)) {
		try {
			callRec = new CallRecord(what[2], CallType::toCallType(what[3]),
					boost::lexical_cast<int>(what[4]), what[5], what[1]);
			return callRec;
		} catch (...) {
			cerr << "Invalid Record Found: " << line << endl;
		}
	}
	return NULL;
}

}

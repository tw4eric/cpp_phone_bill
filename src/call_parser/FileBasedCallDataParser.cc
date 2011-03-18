#include "call_parser/FileBasedCallDataParser.hh"

#include <iostream>
#include <iomanip>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>

using namespace util;
using namespace std;
using namespace boost::xpressive;

namespace CallParser {

    FileBasedCallDataParser::FileBasedCallDataParser(FileReader* fileReader) :
        fileReaderM(fileReader) {}

    FileBasedCallDataParser::FileBasedCallDataParser(const FileBasedCallDataParser& fileBasedCallDataParser)
    : fileReaderM(fileBasedCallDataParser.fileReaderM) {}

    FileBasedCallDataParser::~FileBasedCallDataParser() {}

    list<CallRecord*>* FileBasedCallDataParser::parseRecords() {

        if (!fileReaderM->open()) {
            return 0;
        }

        list<CallRecord*>* callRecordList = new list<CallRecord*> ;

        string line;
        while ((line = fileReaderM->getLine()) != "") {
            CallRecord* callRec = toCallRecord(line);
            if (callRec != 0) {
                callRecordList->push_back(callRec);
            }
        }

        fileReaderM->close();
        return callRecordList;
    }

    CallRecord* FileBasedCallDataParser::toCallRecord(string line) {
        sregex rex = sregex::compile("([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)");
        smatch what;

        CallRecord* callRec = 0;

        if (regex_match(line, what, rex)) {
            cout << "Line matched expected pattern: " << line << endl;
            try {
                callRec = new CallRecord(what[1],CallType::toCallType(what[2]),
                    boost::lexical_cast<int>(what[3]),what[4],what[5]);
                return callRec;
            } catch (...) {
                cerr << "Invalid Record Found: " << line << endl;
                return 0;
            }
        }

        return 0;
    }
}

#include "call_parser/FileBasedCallDataParser.hh"

#include <iostream>
#include <iomanip>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>

using namespace util;
using namespace std;
using namespace boost::xpressive;

namespace CallParser {

/*
<<<<<<< Updated upstream
        FileBasedCallDataParser::FileBasedCallDataParser(string fileName) :
                _fileName(fileName) {
                }

        FileBasedCallDataParser::~FileBasedCallDataParser() {
        }


        list<CallRecord*>* FileBasedCallDataParser::parseRecords() {
                list<CallRecord*>* callRecordList = new list<CallRecord*> ;

                //util::FileReader fileReader(_fileName);
                if (!fileReaderM.open()) {
                        return callRecordList;
                }

                string line;

                while ((line = fileReaderM.getLine()) != "") {
                        CallRecord* callRec = toCallRecord(line);
                        if(callRec != NULL){
                                callRecordList->push_back(callRec);
                        }
                }

                fileReaderM.close();

                return callRecordList;
        }

        CallRecord* FileBasedCallDataParser::toCallRecord(string line) {
                sregex rex =
                        sregex::compile("([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)");
                smatch what;

                CallRecord* callRec=NULL;

                if (regex_match(line, what, rex)) {
                        try{
                                callRec=new CallRecord(what[1],CallType::toCallType(what[2]),
                                                boost::lexical_cast<int>(what[3]),what[4],what[5]);
                                return callRec;
                        }catch(...){
                                cerr<<"Invalid Record Found: "<<line<<endl;
                        }
                }
                return NULL;
        }
*/
    FileBasedCallDataParser::FileBasedCallDataParser(FileReader fileReader) :
        fileReaderM(fileReader) {
    }

    FileBasedCallDataParser::FileBasedCallDataParser(const FileBasedCallDataParser& fileBasedCallDataParser)
    : fileReaderM(fileBasedCallDataParser.fileReaderM)
    {

    }

    FileBasedCallDataParser::~FileBasedCallDataParser() {
    }

    list<CallRecord*>* FileBasedCallDataParser::parseRecords() {
        list<CallRecord*>* callRecordList = new list<CallRecord*> ;

        if (!fileReaderM.open()) {
            return callRecordList;
        }

        string line;
        while ((line = fileReaderM.getLine()) != "") {
            CallRecord* callRec = toCallRecord(line);
            if(callRec != NULL){
                callRecordList->push_back(callRec);
            }
        }

        fileReaderM.close();

        return callRecordList;
    }

    CallRecord* FileBasedCallDataParser::toCallRecord(string line) {
        sregex rex =
                sregex::compile("([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)");
        smatch what;

        CallRecord* callRec=NULL;

        if (regex_match(line, what, rex)) {
            try{
                callRec=new CallRecord(what[1],CallType::toCallType(what[2]),
                    boost::lexical_cast<int>(what[3]),what[4],what[5]);
                return callRec;
            }catch(...){
                cerr<<"Invalid Record Found: "<<line<<endl;
            }
//>>>>>>> Stashed changes
        }
    }
}

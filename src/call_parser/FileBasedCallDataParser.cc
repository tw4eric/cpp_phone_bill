#include "call_parser/FileBasedCallDataParser.hh"

//#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>

#include "util/FileReader.hh"

using namespace std;
using namespace boost::xpressive;

namespace CallParser {

        FileBasedCallDataParser::FileBasedCallDataParser(string fileName) :
                _fileName(fileName) {
                }

        FileBasedCallDataParser::~FileBasedCallDataParser() {
        }

        list<CallRecord*>* FileBasedCallDataParser::parseRecords() {
                list<CallRecord*>* callRecordList = new list<CallRecord*> ;

                //ifstream recFile(_fileName.c_str());
                util::FileReader fileReader(_fileName);
                /*
                   if (!recFile) {
                   cerr << "Unable to open file: " << _fileName << endl;
                   return callRecordList;
                   }
                   */
                if (!fileReader.open()) {
                        return callRecordList;
                }

                string line;

                // while (std::getline(recFile, line)) {
                while ((line = fileReader.getLine()) != "") {
                        CallRecord* callRec = toCallRecord(line);
                        if(callRec != NULL){
                                callRecordList->push_back(callRec);
                        }
                }

                //recFile.close();
                fileReader.close();

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
        }

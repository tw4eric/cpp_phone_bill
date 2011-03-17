#include "call_parser/ParserV5.hh"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::xpressive;

namespace CallParser {

    ParserV5::ParserV5(string fileName) :
        _fileName(fileName) {
    }

    ParserV5::~ParserV5() {
    }

	list<CallRecord*>* ParserV5::parseRecords(){
	}

	bool ParserV5::IsValidFile() {

		ifstream file(_fileName.c_str());
		string line;

		if(file != NULL)
		{
			std::getline(file,line);
			if(line == "#V5") 
				return true ;
		}
		return false;
	}
}

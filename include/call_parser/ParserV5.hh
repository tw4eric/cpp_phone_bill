#ifndef PARSERV5_HH__
#define PARSERV5_HH__

#include<iostream>
#include<fstream>
#include <string>
using namespace std;

#include "CallDataParser.hh"

namespace CallParser {

	class ParserV5 : public CallDataParser {

		public:
			ParserV5(string fileName);
			~ParserV5();
			virtual list<CallRecord*>* parseRecords();
			bool IsValidFile();

		private:
			string _fileName;
			bool _validFile;
			ifstream _infile;

			bool open();
			CallRecord* toRecord(string);
			int toSeconds(int);
			bool IsValidCallerNum(string);
			bool IsValidDate(string);
	};
}


#endif /* PARSERV5_HH__*/

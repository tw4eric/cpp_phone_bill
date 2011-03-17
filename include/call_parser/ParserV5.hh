#ifndef PARSERV5_HH__
#define PARSERV5_HH__


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
	};
}


#endif /* PARSERV5_HH__*/

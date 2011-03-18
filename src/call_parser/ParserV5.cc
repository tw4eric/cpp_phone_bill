#include "call_parser/ParserV5.hh"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/xpressive/xpressive.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::xpressive;

namespace CallParser {

    ParserV5::ParserV5(string fileName) : _fileName(fileName) 
	{
		_validFile = false;
    }

    ParserV5::~ParserV5() 
	{
		_infile.close();
	}

	bool ParserV5::open()
	{
		if( _infile.is_open() )
			return true;

		_infile.open(_fileName.c_str(),ifstream::in);
		return (_infile != NULL);
	}	

	list<CallRecord*>* ParserV5::parseRecords()
	{
		if( IsValidFile() )
		{
			list<CallRecord*>* records = new list<CallRecord*>;
			string frecord;

			while( std::getline(_infile,frecord) )
			{
				CallRecord *record =  NULL;
				record = toRecord(frecord);
				if ( record != NULL ) 
					records->push_back(toRecord(frecord));
			} 
			return records;
		}
		return NULL;
	}

	CallRecord* ParserV5::toRecord( string frecord)
	{
		CallRecord *crecord = NULL;
		int duration = 0;
		string date, caller, callerNum, calltype;

		stringstream sin(frecord);
		sin >> callerNum >> ws >> date >> ws >> calltype >> ws >> dec >> duration >>  ws >> caller;	
		duration = duration / 1000;
		try 
		{
			if( IsValidCallerNum(callerNum) && IsValidDate(date) && !caller.empty() )
			{
				crecord = new CallRecord (date,CallType::toCallType(calltype),toSeconds(duration),caller,callerNum);
			}
		}
		catch (...) {
		}
		return crecord;
	}

	bool ParserV5::IsValidCallerNum(string callerNum)
	{
		int i=0;
		bool valid = false;

		for( ; i < callerNum.length() && isdigit(callerNum[i]); i++);
		if ( i == callerNum.length())
			valid = true;

		return valid;
	}

	bool ParserV5::IsValidDate(string date)
	{
		bool valid = false;
		if( !isdigit(date[2]) && (date[2] == date[5]) )
			valid = true;

		return valid;
	}

	int ParserV5::toSeconds(int duration)
	{
		return (duration/1000);
	}

	bool ParserV5::IsValidFile() 
	{
		if( !_validFile && open() )
		{
			string line;
			std::getline(_infile,line);
			if(line == "#V5")
				_validFile = true;
		}
		return _validFile;
	}
}

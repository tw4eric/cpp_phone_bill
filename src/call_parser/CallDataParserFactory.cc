/*
 * CallDataParserFactory.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: eulagan
 */
#include <fstream>
#include <iostream>
#include "call_parser/CallDataParserFactory.hh"
#include "call_parser/FileBasedCallDataParser.hh"
#include "call_parser/FileBasedCallDataParserV2.hh"
//#include "call_parser/ParserV3.hh"
//#include "call_parser/ParserV4.hh"
//#include "call_parser/ParserV5.hh"
namespace CallParser
{

unsigned int CallDataParserFactory::recognizeParserType(string FileName) const
{
	unsigned int parserId = 0;
	ifstream recFile(FileName.c_str());

	        if (!recFile) {
	            cerr << "Unable to open file: " << FileName << endl;
	            return 0;
	        }

	        string line;

	        if (std::getline(recFile, line))
	        {
	        	const char* pline = line.c_str();
	            if (!(strcmp(pline, "#V2")))
	            {
	            	parserId = 2;
	            }
	            else if (!(strcmp(pline, "#V3")))
	            {
	            	parserId = 3;
	            }
	            else if (!(strcmp(pline, "#V4")))
	            {
	            	parserId = 4;
	            }
	            else if (!(strcmp(pline, "#V5")))
	            {
	            	parserId = 5;
	            }
	            else
	            {
	            	parserId = 1;
	            }
	        }
	        return parserId;
}
CallDataParser* CallDataParserFactory::createParser(string FileName)
{
	unsigned int id = recognizeParserType(FileName);
	switch(id)
	{
		case 1:
		{
			return new FileBasedCallDataParser(FileName);
		}
		case 2:
		{
			return new FileBasedCallDataParserV2(FileName);
		}
		/*
		case 3:
		{
			return new ParserV3();
		}
		case 4:
		{
			return new ParserV4();
		}
		case 5:
		{
			return new ParserV5();
		}
		*/
		default:
		{
			cout<<"This version of Parser is not supported\n";
			return NULL;
		}
	}
}
};

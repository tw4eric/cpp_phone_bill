/*
 * CallDataParserFactory.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: eulagan
 */
#include <fstream>
#include <iostream>
unsigned int CallDataParserFactory::recognizeParserType(string FileName)
{
	unsigned int parserId = 0;
	ifstream recFile(FileName.c_str());

	        if (!recFile) {
	            cerr << "Unable to open file: " << FileName << endl;
	            return 0;
	        }

	        string line;

	        if (std::getline(recFile, line)) {
	            if (!(strcmp(line, "#V2")))
	            {
	            	parserId = 2;
	            }
	            else if (!(strcmp(line, "#V3")))
	            {
	            	parserId = 3;
	            }
	            else if (!(strcmp(line, "#V4")))
	            {
	            	parserId = 4;
	            }
	            else if (!(strcmp(line, "#V5")))
	            {
	            	parserId = 5;
	            }
	            else
	            {
	            	parserId = 1;
	            }
	        }
}
CallParser* CallDataParserFactory::createParser(string FileName)
{
	unsigned int id = recognizeParserType(FileName);
	switch(id)
	{
		case 1:
		{
			return new FileBasedCallDataParser();
		}
		case 2:
		{
			return new ParserV2();
		}
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
		default:
		{
			cout<<"This version of Parser is not supported\n";
			return NULL;
		}
	}
}

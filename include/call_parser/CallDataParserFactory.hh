/*
 * CallDataParserFactory.hh
 *
 *  Created on: Mar 17, 2011
 *      Author: eulagan
 */

#ifndef CALLDATAPARSERFACTORY_HH_
#define CALLDATAPARSERFACTORY_HH_
#include "call_parser/CallDataParser.hh"
#include <cstring>
using namespace std;
namespace CallParser {
class CallDataParserFactory
{
private:
	unsigned int recognizeParserType(string FileName) const;
public:
	CallDataParser* createParser(string FileName);
};
};
#endif /* CALLDATAPARSERFACTORY_HH_ */

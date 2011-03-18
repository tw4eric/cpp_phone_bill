/*
 * CallDataParserFactory.hh
 *
 *  Created on: Mar 17, 2011
 *      Author: eulagan
 */

#ifndef CALLDATAPARSERFACTORY_HH_
#define CALLDATAPARSERFACTORY_HH_
class CallDataParserFactory
{
private:
	unsigned int recognizeParserType(string FileName) const;
public:
	CallParser* createParser(string FileName);
};

#endif /* CALLDATAPARSERFACTORY_HH_ */

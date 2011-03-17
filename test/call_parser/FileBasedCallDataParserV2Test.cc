/*
 * FileBasedCallDataParserV2Test.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: eguaash
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>
using namespace std;
namespace io = boost::iostreams;

#include "call_parser/FileBasedCallDataParserV2.hh"
#include "call_data/CallRecord.hh"
using namespace CallData;
using namespace CallParser;

#include "../TestCommon.hh"
using namespace TestCommon;

#define TEST_CASE FileBasedCallDataParserV2Test

GTEST(shouldNotReadFirstLineOfRecordInFile)
{
    CallDataParser *dataParser = new FileBasedCallDataParserV2("test/call_parser/call_data_small.txt");
    list<CallRecord*>* dataRecords = dataParser->parseRecords();
    EXPECT_TRUE(dataRecords == NULL);
}

GTEST(shouldNotGenerateRecordForInvalidFile)
{
	const char *if_cur_dir_is_root = "test/call_parser/call_data_smallv2.txt";
    CallDataParser *dataParser = new FileBasedCallDataParserV2(if_cur_dir_is_root);
    list<CallRecord*>* dataRecords = dataParser->parseRecords();
    EXPECT_TRUE(dataRecords == NULL);

}



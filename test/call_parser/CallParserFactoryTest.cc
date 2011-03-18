/*
 * CallParserFactoryTest.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: eulagan
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>
using namespace std;
namespace io = boost::iostreams;
#include "call_parser/CallDataParserFactory.hh"
#include "call_parser/FileBasedCallDataParser.hh"
#include "call_parser/FileBasedCallDataParserV2.hh"
#include "call_data/CallRecord.hh"
using namespace CallData;
using namespace CallParser;

#include "../TestCommon.hh"
using namespace TestCommon;

#define TEST_CASE CallDataParserFactoryTest
GTEST(shouldhandleNoneExistingFile)
{
    const char *if_cur_dir_is_test = "call_parser/V2.txt";
    const char *data_file_name = if_cur_dir_is_test;
    CallDataParserFactory *callparserfactory = new CallDataParserFactory();
    CallDataParser *dataParser = callparserfactory->createParser(data_file_name);
    EXPECT_TRUE(dataParser == NULL);
}

GTEST(shouldSupportOldCallRecordFormat)
{
    const char *if_cur_dir_is_test = "test/call_parser/call_data_small.txt";
    const char *data_file_name = if_cur_dir_is_test;
    CallDataParserFactory *callparserfactory = new CallDataParserFactory();
    CallDataParser *dataParser = callparserfactory->createParser(data_file_name);
    EXPECT_TRUE(dataParser != NULL);
}
GTEST(shouldrecognizeV2CallRecordFormat)
{
    const char *if_cur_dir_is_test = "test/call_parser/V2DataFile.txt";
    const char *if_cur_dir_is_root = "call_parser/call_data_small.txt";
    const char *data_file_name = if_cur_dir_is_test;
    FileBasedCallDataParserV2 dummyV2Obj(data_file_name);
    CallDataParserFactory *callparserfactory = new CallDataParserFactory();
    CallDataParser *dataParser = callparserfactory->createParser(data_file_name);
    EXPECT_TRUE(dataParser != NULL);
    EXPECT_STREQ(typeid (dummyV2Obj).name(), typeid (*dataParser).name());
}

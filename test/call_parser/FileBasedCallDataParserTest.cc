#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>
using namespace std;
namespace io = boost::iostreams;

#include "call_parser/FileBasedCallDataParser.hh"
#include "call_data/CallRecord.hh"
using namespace CallData;
using namespace CallParser;

#include "../TestCommon.hh"
using namespace TestCommon;

#define TEST_CASE FileBasedCallDataParserTest


GTEST( shouldGenerateCallRecordForValidInputFile)
{
	const char *if_cur_dir_is_root = "test/call_parser/call_data_small.txt";
	   const char *if_cur_dir_is_test = "call_parser/call_data_small.txt";
	   const char *data_file_name = if_cur_dir_is_root;
    CallDataParser *dataParser = new FileBasedCallDataParser(data_file_name);
    list<CallRecord*>* dataRecords = dataParser->parseRecords();

    EXPECT_TRUE(dataRecords != NULL);
    EXPECT_EQ(3,dataRecords->size());

    ifstream recFile(data_file_name);
    io::filtering_istream in(recFile);
    string output;
    vector<string> linesToCompare;

    while(getline(in, output)) {
        if(output.find("Invalid")==string::npos) {
            linesToCompare.push_back(output);
        }
    }

    int i=0;
    BOOST_FOREACH(CallRecord* rec,*dataRecords) {
        EXPECT_EQ(linesToCompare[i++],rec->operator string());
    }

    release(dataRecords);
}

GTEST(shouldNotGenerateRecordForInvalidFile)
{
    CallDataParser *dataParser = new FileBasedCallDataParser("xx");
    list<CallRecord*>* dataRecords = dataParser->parseRecords();

    EXPECT_TRUE(dataRecords != NULL);
    EXPECT_EQ(0,dataRecords->size());
    release(dataRecords);
}




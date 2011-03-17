#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>
using namespace std;
namespace io = boost::iostreams;

#include "call_parser/ParserV5.hh"
#include "call_data/CallRecord.hh"
using namespace CallData;
using namespace CallParser;

#include "../TestCommon.hh"
using namespace TestCommon;

#define TEST_CASE ParserV5Test

GTEST(shouldParserV5CheckForValidFile)
{
    const char *if_cur_dir_is_root = "test/call_parser/call_data_V5.txt";
    const char *if_cur_dir_is_test = "call_parser/call_data_V5.txt";
    const char *data_file_name = if_cur_dir_is_root;
    ParserV5 *dataParser = new ParserV5(data_file_name);
	bool valid = dataParser->IsValidFile();
	ASSERT_TRUE(valid);
}

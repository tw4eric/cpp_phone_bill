#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <fstream>
#include <string>
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

#include "util/FileReader.hh"

using ::testing::Return;

class MockFileReader : public ::util::FileReader {

public:
	MockFileReader(const string &filename) : FileReader(filename) {}
 public:
  MOCK_METHOD0(open, bool());
  MOCK_METHOD0(getLine, string());
  MOCK_METHOD0(close, void());
};


#define TEST_CASE FileBasedCallDataParserTest

//
//
//GTEST( shouldGenerateCallRecordForValidInputFile)
//{
//	const char *if_cur_dir_is_root = "test/call_parser/call_data_small.txt";
//	   const char *if_cur_dir_is_test = "call_parser/call_data_small.txt";
//	   const char *data_file_name = if_cur_dir_is_root;
//    CallDataParser *dataParser = new FileBasedCallDataParser(data_file_name);
//=======
GTEST(countOftheCallRecordsMustBeEqualToNumberOfValidEntries)
{
    const string data_file_name("dummyfile");
    MockFileReader fileReader(data_file_name);
    EXPECT_CALL(fileReader, open()).Times(1);
    EXPECT_CALL(fileReader, getLine())
        .Times(7)
        .WillOnce(Return("21/02/2011 LOC 5 Nick 974503244"))
        .WillOnce(Return("04/01/2011 LOC MNO InvalidRecord 164503234"))
		.WillOnce(Return("23/02/2011 STD 1 Dale 864503214"))
		.WillOnce(Return("04/01/2011 XXX 30 InvalidRecord 164503234"))
		.WillOnce(Return("04/01/2011 ISD 30 Nick 164503234"))
		.WillOnce(Return("04/01/2011ISD 30 InvalidRecord 164503234"))
        .WillOnce(Return(""));
    EXPECT_CALL(fileReader, close()).Times(1);
    CallDataParser *dataParser = new FileBasedCallDataParser(fileReader);
    list<CallRecord*>* dataRecords = dataParser->parseRecords();

    EXPECT_TRUE(dataRecords != NULL);
    EXPECT_EQ(3,dataRecords->size());

    release(dataRecords);
}

GTEST(shouldGenerateOneCallRecord)
{
    const string data_file_name("dummyfile");
    MockFileReader fileReader(data_file_name);
    EXPECT_CALL(fileReader, open()).Times(1);
    EXPECT_CALL(fileReader, getLine())
        .Times(2)
        .WillOnce(Return("21/02/2011 LOC 5 Nick 974503244"))
        .WillOnce(Return(""));
    EXPECT_CALL(fileReader, close()).Times(1);
    CallDataParser *dataParser = new FileBasedCallDataParser(fileReader);
    list<CallRecord*>* dataRecords = dataParser->parseRecords();

    EXPECT_TRUE(dataRecords != NULL);
    EXPECT_EQ(1,dataRecords->size());

    BOOST_FOREACH(CallRecord* rec,*dataRecords) {
        EXPECT_EQ("21/02/2011 LOC 5 Nick 974503244",rec->operator string());
    }

    release(dataRecords);
}

GTEST(shouldNotGenerateCallRecordForEntryWithInvalidCallDuration)
{
    const string data_file_name("dummyfile");
    MockFileReader fileReader(data_file_name);
    EXPECT_CALL(fileReader, open()).Times(1);
    EXPECT_CALL(fileReader, getLine())
        .Times(2)
        .WillOnce(Return("04/01/2011 LOC MNO InvalidRecord 164503234"))
        .WillOnce(Return(""));
    EXPECT_CALL(fileReader, close()).Times(1);
    CallDataParser *dataParser = new FileBasedCallDataParser(fileReader);
    list<CallRecord*>* dataRecords = dataParser->parseRecords();

    EXPECT_TRUE(dataRecords == NULL);
}


/*
GTEST(shouldGenerateCallRecordForValidInputFile)
{
    const char *if_cur_dir_is_root = "test/call_parser/call_data_small.txt";
    const char *if_cur_dir_is_test = "call_parser/call_data_small.txt";
    const char *data_file_name = if_cur_dir_is_root;
    MockFileReader fileReader(data_file_name);
    EXPECT_CALL(fileReader, getLine())
        .Times(7)
        .WillOnce(Return("21/02/2011 LOC 5 Nick 974503244"))
        .WillOnce(Return("04/01/2011 LOC MNO InvalidRecord 164503234"))
		.WillOnce(Return("23/02/2011 STD 1 Dale 864503214"))
		.WillOnce(Return("04/01/2011 XXX 30 InvalidRecord 164503234"))
		.WillOnce(Return("04/01/2011 ISD 30 Nick 164503234"))
        .WillOnce(Return("04/01/2011ISD 30 InvalidRecord 164503234"));
    CallDataParser *dataParser = new FileBasedCallDataParser(fileReader);
>>>>>>> Stashed changes
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
*/

GTEST(shouldNotGenerateRecordForInvalidFile)
{
    util::FileReader fileReader("xx");
	CallDataParser *dataParser = new FileBasedCallDataParser(fileReader);
    list<CallRecord*>* dataRecords = dataParser->parseRecords();

    EXPECT_TRUE(dataRecords != NULL);
    EXPECT_EQ(0,dataRecords->size());
    release(dataRecords);
}




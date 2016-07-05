#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

#include <cpp/util/Base64.h>

using namespace cpp::util;
class Base64Test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Base64Test);
	CPPUNIT_TEST(testEncode);
	CPPUNIT_TEST(testDecode);
	CPPUNIT_TEST_SUITE_END();

public:
	void testEncode();
	void testDecode();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Base64Test);

void Base64Test::testEncode()
{
	std::string testString1 = "";
	std::string testString2 = "a";
	std::string testString3 = "ab";
	std::string testString4 = "abc";
	std::string testString5 = "abcd";
	std::string testString6 = "abcde";
	std::string testString7 = "abcdef";
	std::string testString8 = "abcdefg";
	std::string testString9 = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";	
	std::string testString9Result = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString1).compare(""),0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString2).compare("YQ=="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString3).compare("YWI="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString4).compare("YWJj"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString5).compare("YWJjZA=="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString6).compare("YWJjZGU="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString7).compare("YWJjZGVm"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString8).compare("YWJjZGVmZw=="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString9).compare(testString9Result), 0);

}

void Base64Test::testDecode()
{
	std::string testString1 = "";
	std::string testString2 = "YQ==";
	std::string testString3 = "YWI=";
	std::string testString4 = "YWJj";
	std::string testString5 = "YWJjZA==";
	std::string testString6 = "YWJjZGU=";
	std::string testString7 = "YWJjZGVm";
	std::string testString8 = "YWJjZGVmZw==";
	std::string testString9 = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
	std::string testString9Result = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";

	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString1).compare(""), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString2).compare("a"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString3).compare("ab"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString4).compare("abc"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString5).compare("abcd"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString6).compare("abcde"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString7).compare("abcdef"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString8).compare("abcdefg"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::decode(testString9).compare(testString9Result), 0);
}


int main(int argc, char ** argv)
{
	std::cout << "Bas64 Test" << std::endl;
	CPPUNIT_NS::TestResult controller;
	CPPUNIT_NS::TestResultCollector result;
	controller.addListener(&result);

	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener(&progress);

	CPPUNIT_NS::TestRunner runner;
	runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	runner.run(controller);

	CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
	outputter.write();

	return 0;
}
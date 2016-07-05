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
	CPPUNIT_TEST(testSolution);
	CPPUNIT_TEST_SUITE_END();

public:
	void testSolution();
};

CPPUNIT_TEST_SUITE_REGISTRATION(Base64Test);

void Base64Test::testSolution()
{
	std::string testString1 = "";
	std::string testString2 = "a";
	std::string testString3 = "ab";
	std::string testString4 = "abc";
	std::string testString5 = "abcd";
	std::string testString6 = "abcde";
	std::string testString7 = "abcdef";
	std::string testString8 = "abcdefg";
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString1).compare(""),0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString2).compare("YQ=="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString3).compare("YWI="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString4).compare("YWJj"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString5).compare("YWJjZA=="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString6).compare("YWJjZGU="), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString7).compare("YWJjZGVm"), 0);
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString8).compare("YWJjZGVmZw=="), 0);
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
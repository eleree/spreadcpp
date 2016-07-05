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
	std::string testString1 = "abc";
	CPPUNIT_ASSERT_EQUAL(Base64::encode(testString1).compare("YWJj"),0);
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
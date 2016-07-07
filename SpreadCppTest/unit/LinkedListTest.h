#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

#include <cpp/util/LinkedList.h>

using namespace cpp::util;
class LinkedListTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(LinkedListTest);
	CPPUNIT_TEST(testModify);
	CPPUNIT_TEST_SUITE_END();

public:
	void testModify();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LinkedListTest);


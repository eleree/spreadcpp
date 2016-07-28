#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

#include <cpp/lang/String.h>

using namespace cpp::lang;
class StringTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(StringTest);
	CPPUNIT_TEST(testString);
	CPPUNIT_TEST_SUITE_END();

public:
	void testString();
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringTest);


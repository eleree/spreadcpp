#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

#include <cpp/net/HttpUrl.h>

using namespace cpp::net;
class HttpUrlTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(HttpUrlTest);
	CPPUNIT_TEST(testUrl);
	CPPUNIT_TEST_SUITE_END();

public:
	void testUrl();
};

CPPUNIT_TEST_SUITE_REGISTRATION(HttpUrlTest);


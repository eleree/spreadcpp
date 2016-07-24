#include "HttpHeaderTest.h"


void HttpHeaderTest::testModify(void)
{
	HttpHeader httpHeader;
	httpHeader.set("", "");
	CPPUNIT_ASSERT_EQUAL(httpHeader.get("").compare(""), 0);
	CPPUNIT_ASSERT_EQUAL((int)httpHeader.size(), 0);
	httpHeader.set("", "ABCD");
	CPPUNIT_ASSERT_EQUAL(httpHeader.get("").compare(""), 0);
	CPPUNIT_ASSERT_EQUAL((int)httpHeader.size(), 0);
	httpHeader.set("ABCD", "");
	CPPUNIT_ASSERT_EQUAL(httpHeader.get("ABCD").compare(""), 0);
	CPPUNIT_ASSERT_EQUAL((int)httpHeader.size(), 0);
	httpHeader.set("ABCD", "EFGH");
	CPPUNIT_ASSERT_EQUAL(httpHeader.get("ABCD").compare("EFGH"), 0);
	CPPUNIT_ASSERT_EQUAL((int)httpHeader.size(), 1);
	CPPUNIT_ASSERT_EQUAL(httpHeader.toString().compare("ABCD:EFGH\r\n"), 0);

}
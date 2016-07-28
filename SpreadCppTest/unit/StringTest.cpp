#include "StringTest.h"

void StringTest::testString(void)
{
	string a = "AB";
	string b = "ACABCD";
	CPPUNIT_ASSERT_EQUAL(0, 0);
	CPPUNIT_ASSERT_EQUAL((int)String::regionMatches(a, 0, b, 2, 2), 1);

}

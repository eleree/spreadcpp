#include "HttpUrlTest.h"

void HttpUrlTest::testUrl()
{
	// test host
	string testUrl1 = "http://android.com"; 
	string testUrl2 = "http://127.0.0.1/";
	string testUrl3 = "http://xn--n3h.net/";
	string testUrl4 = "http://[::1]/";
	
	CPPUNIT_ASSERT_EQUAL(HttpUrl::parse("https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf(int)").host().compare("docs.oracle.com"), 0);
	CPPUNIT_ASSERT_EQUAL(HttpUrl::parse(" \t\fhttp://127.0.0.1/    ").host().compare("127.0.0.1"), 0);
	CPPUNIT_ASSERT_EQUAL(HttpUrl::parse("http://127.0.0.1/").host().compare("127.0.0.1"), 0);
	CPPUNIT_ASSERT_EQUAL(HttpUrl::parse("  \t\f\nhttp://android.com").host().compare("android.com"), 0);
	CPPUNIT_ASSERT_EQUAL(HttpUrl::parse(" http://android.com \t\f\n").host().compare("android.com"), 0);
	CPPUNIT_ASSERT_EQUAL(HttpUrl::parse("http://android.com \t\f\n").host().compare("android.com"), 0);
	CPPUNIT_ASSERT_EQUAL(HttpUrl::parse("http://android.com/login.html \t\f\n").host().compare("android.com"), 0);

	//CPPUNIT_ASSERT_EQUAL(HttpUrl::parse(testUrl3).host().compare(""), 0);
	//CPPUNIT_ASSERT_EQUAL(HttpUrl::parse(testUrl4).host().compare(""), 0);
}

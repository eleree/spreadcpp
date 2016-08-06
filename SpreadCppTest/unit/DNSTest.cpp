#include "DNSTest.h"

void DNSTest::testDns(void)
{
	string a = "AB";
	string b = "ACABCD";
	CPPUNIT_ASSERT_EQUAL(0, 0);

	list<string> ipv4Address = DNS::Instance("baidu.com", 80)->getIPv4Address();
	cout << ipv4Address.size() << endl;
	for (auto && a : ipv4Address)
		cout << a << endl;
}

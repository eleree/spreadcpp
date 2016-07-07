#include "LinkedListTest.h"

using namespace cpp::util;

void LinkedListTest::testModify()
{
	LinkedList<int> testList;
	CPPUNIT_ASSERT_EQUAL(testList.size(), 0);
	testList.add(0);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 1);
	testList.add(1);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 2);
}
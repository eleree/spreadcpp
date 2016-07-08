#include "LinkedListTest.h"

using namespace cpp::util;

void LinkedListTest::testModify()
{
	LinkedList<int> testList;
	CPPUNIT_ASSERT_EQUAL(testList.size(), 0);
	testList.add(0);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 1);
	CPPUNIT_ASSERT_EQUAL(testList.front(), 0);
	CPPUNIT_ASSERT_EQUAL(testList.back(), 0);
	testList.add(1);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 2);
	CPPUNIT_ASSERT_EQUAL(testList.front(), 0);
	CPPUNIT_ASSERT_EQUAL(testList.back(), 1);
	testList.add(2);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 3);
	CPPUNIT_ASSERT_EQUAL(testList.front(), 0);
	CPPUNIT_ASSERT_EQUAL(testList.back(), 2);
	testList.remove(2);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 2);
	CPPUNIT_ASSERT_EQUAL(testList.front(), 0);
	CPPUNIT_ASSERT_EQUAL(testList.back(), 1);
	testList.remove(0);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 1);
	CPPUNIT_ASSERT_EQUAL(testList.front(), 1);
	CPPUNIT_ASSERT_EQUAL(testList.back(), 1);

	testList.clear();
	CPPUNIT_ASSERT_EQUAL(testList.size(), 0);

	int i = 0;
	for (i = 0; i < 100; i++)
		testList.add(i);
	CPPUNIT_ASSERT_EQUAL(testList.size(), 100);
	i = 0;
	for (LinkedList<int>::iterator it = testList.begin(); it != testList.end(); ++it)
		CPPUNIT_ASSERT_EQUAL(*it, i++);
}
#include "ThreadTest.h"
#include <cpp/lang/Thread.h>
#include <cpp/util/Mutex.h>
#include <cpp/util/LockGuard.h>
using namespace cpp::util;

class TestThread : public Thread
{
public:
	TestThread() :_isStop(Thread::RUNNING){}
	void run(void)
	{
		int i = 0;
		while (_isStop == Thread::RUNNING)
		{
			cout << "Test "<< i++ << endl;
			Thread::sleep(1000);
		}

	}

	void stop()
	{
		_isStop = Thread::STOP;
	}
private:
	int32_t _isStop;
};



Mutex mutex;

class TestMutexThread : public Thread
{
public:
	TestMutexThread(int32_t v) :_isStop(Thread::RUNNING), _testValue(v){}
	void run(void)
	{
		int i = 0;
		while (_isStop == Thread::RUNNING)
		{
			LockGuard lock(mutex);
			cout << "TestTestTestTestTestTestTestTestTest - " << _testValue << endl;
		}

	}

	void stop()
	{
		_isStop = Thread::STOP;
	}
private:
	int32_t _isStop;
	int32_t _testValue;
};

void ThreadTest::testThread()
{
	TestThread *testThread = new TestThread();
	testThread->start();
	Thread::sleep(3000);
	testThread->stop();
	testThread->join(0);
	CPPUNIT_ASSERT_EQUAL(testThread->status(), (int32_t)Thread::STOP);
	delete testThread;
	cout << "Test Terminate Thread" << endl;
	testThread = new TestThread();
	testThread->start();
	Thread::sleep(500);
	testThread->terminate(-1);
	CPPUNIT_ASSERT_EQUAL(testThread->status(), (int32_t)Thread::TERMINATED);
	delete testThread;

	//TestMutexThread *testMutexThread1 = new TestMutexThread(1);
	//TestMutexThread *testMutexThread2 = new TestMutexThread(2);
	//testMutexThread1->start();
	//testMutexThread2->start();
}
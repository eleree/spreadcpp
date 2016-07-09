#include <cpp/util/ArrayList.h>
#include <cpp/util/LinkedList.h>
#include <cpp/lang/Thread.h>
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
			cout << "Test" << endl;
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

int main(int argc, char ** argv)
{
	TestThread *testThread = new TestThread();
	testThread->start();
	Thread::sleep(3000);
	testThread->stop();
	testThread->join(0);
	delete testThread;

	cout << "Terminate Thread" << endl;
	testThread = new TestThread();
	testThread->start();
	Thread::sleep(1000);
	testThread->terminate(-1);
	Thread::sleep(5000);
	return 0;
}
#include <cpp/util/ArrayList.h>
#include <cpp/util/LinkedList.h>
#include <cpp/lang/Thread.h>
#include <cpp/util/Timer.h>
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

class TestTimerTask : public Timer::TimerTask
{
	void run(){
		cout << "Test Timer Task" << endl;
	}
};
 
class TestInnerTimerTask
{
public:
	TestInnerTimerTask() : x(2), _timerTask(this)
	{
		cout << "Outter Timer Task" << endl; 
	}

	class TestTimerTask : public Timer::TimerTask
	{
	public:
		TestTimerTask(TestInnerTimerTask * const t) :_innerTimerTask(t)
		{
			cout << "Inner Task" << endl;
		}
		void run(){
			cout << "Test Inner Timer Task" << endl;
		}
	private:
		TestInnerTimerTask * _innerTimerTask;
		friend class TestInnerTimerTask;
	};

	TestTimerTask _timerTask;

private:
	int32_t x;
};

int main(int argc, char ** argv)
{
	Timer timer;
	TestInnerTimerTask *testInnerTimerTask = new TestInnerTimerTask();
	//TestTimerTask *testTimerTask = new TestTimerTask();
	//timer.schedule(testTimerTask, 1, 1);
	timer.schedule(&testInnerTimerTask->_timerTask, 1, 1);

	return 0;
	/*
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
	*/
}
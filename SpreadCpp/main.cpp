#include <cpp/util/ArrayList.h>
#include <cpp/util/LinkedList.h>
#include <cpp/lang/Thread.h>
#include <cpp/util/Timer.h>
#include <cpp/util/Mutex.h>
#include <cpp/util/LockGuard.h>
#include <cpp/net/HttpUrl.h>

using namespace cpp::util;
using namespace cpp::net;

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
	//Timer timer;
	//TestInnerTimerTask *testInnerTimerTask = new TestInnerTimerTask();
	//TestTimerTask *testTimerTask = new TestTimerTask();
	//timer.schedule(testTimerTask, 1, 1);
	//timer.schedule(&testInnerTimerTask->_timerTask, 1, 1);
	//return 0;
	{
		auto httpUrl = std::make_shared<HttpUrl>();
		httpUrl->scheme("http").username("chin");
		cout << httpUrl->scheme() << httpUrl->username() << endl;
	}

	system("pause");

	return 0;
}
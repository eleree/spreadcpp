#define WIN32_LEAN_AND_MEAN

#include <cpp/util/ArrayList.h>
#include <cpp/util/LinkedList.h>
#include <cpp/lang/Thread.h>
#include <cpp/util/Timer.h>
#include <cpp/util/Mutex.h>
#include <cpp/util/LockGuard.h>
#include <cpp/net/HttpUrl.h>
#include <cpp/net/Socket.h>
#include <cpp/net/SocketFactory.h>


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

	string x = "中";
	for (size_t i = 0; i < strlen(x.c_str()); i++)
		printf("%#02X ",(uint8_t)(*(x.c_str()+i)));
	cout << x << endl;
	uint8_t utf8Test[] = { 0xE4,0xB8,0xAD,0x00 };
	printf("%s", utf8Test);
	printf("\n");

	{
		auto httpUrl = std::make_shared<HttpUrl>();
		httpUrl->scheme("http").username("chin").password("1234").host("www.google.com");
		cout << httpUrl->scheme() << httpUrl->username() << endl;
		cout << httpUrl->host() << endl;
		cout << httpUrl->toString() << endl;
	}

	
	system("pause");

	return 0;
}
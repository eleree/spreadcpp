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
#include <cpp/lang/String.h>
#include <cpp/lang/UTF8CharsetEncoder.h>
#include <cpp/net/HttpClient.h>
#include <cpp/net/DNS.h>
using namespace cpp::util;
using namespace cpp::net;
using namespace cpp::lang;

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
	/*
	string x = "严";
	x = String::convert(x, String::Charset::GB2312, String::Charset::UTF8);
	for (size_t i = 0; i < strlen(x.c_str()); i++)
		printf("%#02X ",(uint8_t)(*(x.c_str()+i)));
	cout << endl;
	cout << x << endl;
	uint8_t utf8Test[] = { 0x4E,0x2D,0x00 };//中
	printf("-------------------\n");
	x = String::convert((string)(const char *)utf8Test, String::Charset::UNICODE, String::Charset::UTF8);
	cout << x << endl;
	for (size_t i = 0; i < strlen(x.c_str()); i++)
		printf("%#02X ", (uint8_t)(*(x.c_str() + i)));
	cout << endl;

	{
		auto httpUrl = std::make_shared<HttpUrl>();
		httpUrl->scheme("http").username("chin").password("1234").host("www.google.com");
		cout << httpUrl->scheme() << httpUrl->username() << endl;
		cout << httpUrl->host() << endl;
		cout << httpUrl->toString() << endl;
	}
	*/

	/*
	{
		shared_ptr<Test> t = make_shared<Test>();
	}
	
	{
		shared_ptr<HttpClient> xxxx = HttpClient::getInstance();
		xxxx->test();
		shared_ptr<HttpClient> httpClient = HttpClient::getInstance();
		httpClient->test();		
		cout << httpClient.use_count() << endl;
	}
	*/

	DNS dns("taobao.com", 80);
	dns.resolve(50);
	system("pause");
	shared_ptr<HttpClient> httpClient = HttpClient::getInstance();

	HttpRequest httpRequest;
	HttpResponse httpResponse  = httpClient->execute(httpRequest);
	if (httpResponse.isSuccess())
	{
		cout << httpResponse.body().toString() << endl;
	}else{
		cout << "Request Http Request Fail" << endl;
	}

	system("pause");

	return 0;
}

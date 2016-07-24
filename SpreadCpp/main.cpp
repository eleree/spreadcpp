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

	#define DEFAULT_BUFLEN 512
	//char sendbuf[] = "GET /login.html HTTP/1.1\r\nHost: 192.168.1.1\r\n\
				Connection : keep - alive\r\n\
				Cache - Control: max - age = 0\r\n\
			    Accept : text / html, application / xhtml + xml, application / xml; q = 0.9, image / webp, */*;q=0.8\r\n\
				User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.134 Safari/537.36\r\n\
				DNT: 1\r\n\
				Accept-Encoding: gzip, deflate, sdch\r\n\
				Accept-Language: zh-CN,zh;q=0.8\r\n\
				Cookie: language=en_US\r\n\
				If-Modified-Since: Tue Jul 19 16:02:43 2016\r\n\0";
	//char *sendbuf = "GET /login.html HTTP/1.1\r\n  ";
	char *sendbuf =   "GET /login.html HTTP/1.1 \r\n\Host: 192.168.1.1\r\n\
				Connection : keep - alive\r\n\
				Cache - Control: max - age = 0\r\n\
			    Accept : text / html, application / xhtml + xml, application / xml; q = 0.9, image / webp, */*;q=0.8\r\n\
				User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.134 Safari/537.36\r\n\
				DNT: 1\r\n\
				Accept-Encoding: gzip, deflate, sdch\r\n\
				Accept-Language: zh-CN,zh;q=0.8\r\n\
				Cookie: language=en_US\r\n\
				If-Modified-Since: Tue Jul 19 16:02:43 2016\r\n\0";
	char recvbuf[DEFAULT_BUFLEN];
	memset(recvbuf, 0, DEFAULT_BUFLEN);
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	Socket clientSocket;
	clientSocket.connect("192.168.18.106", 80);
	cout << clientSocket.send(sendbuf, (int)strlen(sendbuf)) << endl;
	do {

		iResult = clientSocket.recv(recvbuf, recvbuflen);
		if (iResult > 0)
			printf("Bytes received: %d,%s\n", iResult, recvbuf);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

	clientSocket.close();
	system("pause");

	return 0;
}
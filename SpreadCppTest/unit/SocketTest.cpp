#include "SocketTest.h"

void SocketTest::testSocket(void)
{
#define DEFAULT_BUFLEN 512

	char *sendbuf = "GET /login.html HTTP/1.1 \r\nHost: 192.168.1.1\r\n\
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
}
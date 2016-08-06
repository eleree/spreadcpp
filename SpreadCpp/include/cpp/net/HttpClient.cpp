#include <cpp/lang/String.h>
#include <cpp/net/HttpClient.h>

using namespace std;
using namespace cpp::net;
using namespace cpp::lang;

weak_ptr<HttpClient> HttpClient::_httpClient;

shared_ptr<HttpClient> HttpClient::getInstance(void)
{
	shared_ptr<HttpClient> httpClient;
	cout << "Instance:" << HttpClient::_httpClient.use_count() << endl;
	if (HttpClient::_httpClient.use_count() == 0)
	{
		cout << "Build Http Client" << endl;
		httpClient = std::make_shared<HttpClient>(ctor_cookie());
		_httpClient = httpClient;
		return httpClient;
	}
	else
	{
		return _httpClient.lock();
	}
}

HttpResponse HttpClient::execute(HttpRequest request)
{
	HttpResponse httpResponse;
	httpResponse = retryAndFollowInterceptor(request);	
	return httpResponse;
}

int32_t HttpClient::enqueue(HttpRequest request, shared_ptr<HttpCallback> callback)
{	
	return 0;
}

HttpRequest HttpClient::followUp(HttpResponse response)
{
	HttpRequest httpRequest;
	httpRequest.follow(false);
	return httpRequest;
}

HttpResponse HttpClient::retryAndFollowInterceptor(HttpRequest request)
{
	uint32_t maxFollow = 20;
	HttpResponse httpResponse;
	while (1)
	{
		httpResponse = BridgeInterceptor(request);
		if (httpResponse.status() == HttpResponse::ROUTE_FAIL)
		{

		}else if (httpResponse.status() == HttpResponse::CONNECT_FAIL){

		}

		HttpRequest followRequest = followUp(httpResponse);

		if (!followRequest.needFollow())
			return httpResponse;

		if (--maxFollow)
		{
			httpResponse.status(HttpResponse::FOLLOW_OVERFLOW);
			break;
		}

	}
	
	return httpResponse;
}

HttpResponse HttpClient::BridgeInterceptor(HttpRequest request)
{
	cout << request.toString() << endl;

	if (request.header().get("Host").compare("") == 0)
	{
		request.header().set("Host", "192.168.1.1");
	}

	if (request.header().get("Connection").compare("") == 0)
	{
		request.header().set("Connection", "Keep-Alive");
	}

	if (request.header().get("User-Agent").compare("") == 0)
	{
		request.header().set("User-Agent", "Spread HttpClient");
	}
	request.header().set("Cache-Control", " max-age=0");
	request.header().set("Accept-Encoding", " gzip, deflate, sdch");
	request.header().set("Accept-Language", " zh-CN,zh;q=0.8");
	request.header().set("Accept", " text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");


	cout << request.header().toString() << endl;
	HttpResponse httpResponse = CacheInterceptor(request);

	return httpResponse;
}

HttpResponse HttpClient::CacheInterceptor(HttpRequest request)
{
	HttpResponse httpResponse = NetworkInterceptor(request);
	return httpResponse;

}

HttpResponse HttpClient::NetworkInterceptor(HttpRequest request)
{
	int32_t rc = 0;
	HttpResponse httpResponse;
	Socket clientSocket;
	clientSocket.connect("192.168.18.1", 80, 10000);
	cout << "Start Connecting Socket" << endl;
	string httpHeader = request.toHttpString();
	rc = clientSocket.send((char *)httpHeader.c_str(), httpHeader.size());
	if (rc<0)
	{
		httpResponse.status(HttpResponse::TIMEOUT);
		return httpResponse;
	}
	cout << "Start Socket Receive" << endl;

	#define DEFAULT_BUFLEN 512
	int iResult = 1;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	memset(recvbuf, 0, DEFAULT_BUFLEN);
	do {
		string rawResponse = clientSocket.readline();
		if (rawResponse.empty())
			break;
		string HTTP11 = "HTTP/1.1";
		if (String::regionMatches(rawResponse, 0, HTTP11, 0, 8) == true)
		{
			httpResponse.status(std::stoi(String::substring(rawResponse,8), nullptr, 10));
		}
		int32_t equalToken = String::indexOf(rawResponse, ':');
		if (equalToken > 0)
			httpResponse.header().set(String::substring(rawResponse, 0, equalToken), \
									String::substring(rawResponse,equalToken+1));
		cout << rawResponse << endl;
		continue;
		iResult = clientSocket.recv(recvbuf, recvbuflen);
		if (iResult > 0)
			printf("Bytes received: %d,%s\n", iResult, recvbuf);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);
	httpResponse.setSuccessStatus(true);
	cout << "Http Status: " << httpResponse.status() << endl;
	cout << httpResponse.toString() << endl;
	return httpResponse;
}

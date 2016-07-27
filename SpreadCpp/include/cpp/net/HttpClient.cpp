#include <cpp/net/HttpClient.h>

using namespace std;
using namespace cpp::net;

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
	HttpResponse httpResponse;
	cout << request.toString() << endl;
	cout << request.header().toString() << endl;

	if (request.header().get("Host").compare("") == 0)
	{
		request.header().set("Host", "192.168.1.1:8080");
		cout << request.header().toString() << endl;
	}

	return httpResponse;
}
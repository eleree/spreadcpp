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
	httpResponse.setSuccessStatus(true);
	return httpResponse;
}
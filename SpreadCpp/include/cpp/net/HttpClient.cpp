#include <cpp/lang/String.h>
#include <cpp/net/HttpClient.h>
#include <cpp/net/DNS.h>

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
	httpRequest.follow(true);
	return httpRequest;
}

HttpResponse HttpClient::retryAndFollowInterceptor(HttpRequest request)
{
	uint32_t maxFollow = 3;
	HttpResponse httpResponse;
	while (1)
	{
		httpResponse = BridgeInterceptor(request);
		if (httpResponse.status() == HttpResponse::ROUTE_FAIL)
		{

		}else if (httpResponse.status() == HttpResponse::CONNECT_FAIL){

		}

		if (httpResponse.status() == HttpResponse::SUCCESS)
		{
			if (httpResponse.httpStatus() == HttpStatus::HTTP_OK)
			{
				cout << "OK" << endl;
				break;
			}// Http Code 200

			if (httpResponse.httpStatus() == HttpStatus::HTTP_MOVED_PERM)
			{
				cout << "Resource Move Permantly" << endl;
				request.url(httpResponse.header().get("Location"));
				continue;
			}

			if (httpResponse.httpStatus() == HttpStatus::HTTP_MOVED_TEMP)
			{
				cout << "Redirect: " << httpResponse.header().get("Location")  << endl;
				request.url(httpResponse.header().get("Location"));
			
				if (!request.needFollow())
					return httpResponse;

				if (--maxFollow == 0)
				{
					httpResponse.status(HttpResponse::FOLLOW_OVERFLOW);
					break;
				}

				continue;
			}// Http Code 302


			return httpResponse;
		}
		
	}
	
	return httpResponse;
}

HttpResponse HttpClient::BridgeInterceptor(HttpRequest request)
{
	cout << request.toString() << endl;

	if (request.header().get("Host").compare("") == 0)
	{
		request.header().set("Host", request.url().host());
	}

	if (request.header().get("Connection").compare("") == 0)
	{
		request.header().set("Connection", "keep-alive");
	}

	if (request.header().get("User-Agent").compare("") == 0)
	{
		request.header().set("User-Agent", "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.134 Safari/537.36");
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
	HttpResponse httpResponse = ConnectionInterceptor(request);
	return httpResponse;
}

HttpResponse HttpClient::ConnectionInterceptor(HttpRequest request)
{
	HttpResponse httpResponse;
	shared_ptr<HttpConnection> connection = _connectionPool->findIdleConnection(request.url().scheme(), request.url().host());
	if (connection == nullptr)
	{
		httpResponse.status(HttpResponse::NO_VALID_CONNECTION);
		return httpResponse;
	}

	// Find a idle connection, if no idle connection found, new one;
	httpResponse = NetworkInterceptor(request, connection);
	
	// if no Content-length return, release this 
	cout << httpResponse.header().get("Content-Length") << endl;
	if (httpResponse.header().get("Content-Length").compare("") != 0)
	{		
		int32_t contentLength = std::stoi(httpResponse.header().get("Content-Length"), 0, 10);
		cout << "Content-length:" << std::stoi(httpResponse.header().get("Content-Length"), 0, 10) << endl;
		//httpResponse.body().init(0, contentLength, connection);
		httpResponse.body(make_shared<HttpResponseBody>(0, contentLength, HttpResponseBody::RESPONSE_BODY_FIX_LENGTH ,connection));
	}else{
		if (httpResponse.header().get("Transfer-Encoding").compare("chunked") != 0)
		{
			cout << "Connection Chunkedy" << endl;
			httpResponse.body(make_shared<HttpResponseBody>(0, 0, HttpResponseBody::RESPONSE_BODY_CHUNKED, connection));
		}else{
			cout << "Unknown Connection" << endl;
			httpResponse.body(make_shared<HttpResponseBody>(0, 0, HttpResponseBody::RESPONSE_BODY_UNKNOWN, connection));
		}
		//connection->release();
	}

	// Connection Route Fail
	return httpResponse;
}

HttpResponse HttpClient::NetworkInterceptor(HttpRequest request, shared_ptr<HttpConnection> connection)
{
	int32_t rc = 0;
	HttpResponse httpResponse;
	
	list<string> ipv4Address = DNS::Instance(request.url().host(), 80)->getIPv4Address();
	for (auto && a : ipv4Address)
		cout << a << endl;
	auto address = ipv4Address.begin();
	cout << "Use IP:" << *address << endl;
	connection->setAddress(request.url().scheme(), *address, request.url().port());
	connection->connectSocket(5000, 5000);

	cout << "Start Connecting Socket" << endl;
	string httpHeader = request.toHttpString();
	cout << "Http Header:" << httpHeader << endl;

	rc = connection->write((char *)httpHeader.c_str(), httpHeader.size());

	if (rc<0)
	{
		httpResponse.status(HttpResponse::TIMEOUT);
		return httpResponse;
	}
	cout << "Start Socket Receive" << endl;

	do {
		string rawResponse = connection->readline();
		if (rawResponse.empty())
			break;
		string HTTP11 = "HTTP/1.1";
		string HTTP10 = "HTTP/1.0";
		if (String::regionMatches(rawResponse, 0, HTTP11, 0, 8) == true)
		{
			httpResponse.httpStatus(std::stoi(String::substring(rawResponse,8), nullptr, 10));
		}else if(String::regionMatches(rawResponse, 0, HTTP10, 0, 8) == true){
			httpResponse.httpStatus(std::stoi(String::substring(rawResponse, 8), nullptr, 10));
		}
		int32_t equalToken = String::indexOf(rawResponse, ':');
		if (equalToken > 0)
			httpResponse.header().set(String::substring(rawResponse, 0, equalToken), \
									String::substring(rawResponse,equalToken+1));
	} while(1);

	httpResponse.setSuccessStatus(true);
	httpResponse.status(HttpResponse::SUCCESS);
	cout << "Http Response Status: " << httpResponse.httpStatus() << endl;
	cout << "Http Response Header: " << httpResponse.toString() << endl;
	return httpResponse;
}

#ifndef _CPP_NET_HTTP_CLIENT_H_
#define _CPP_NET_HTTP_CLIENT_H_

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <list>
#include <memory>

#include <cpp/net/Socket.h>
#include <cpp/net/HttpRequest.h>
#include <cpp/net/HttpResponse.h>
#include <cpp/net/HttpCallback.h>
#include <cpp/net/HttpConnection.h>
#include <cpp/net/HttpConnectionPool.h>
using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpClient{
		public:
			struct ctor_cookie {};
			explicit HttpClient(ctor_cookie) 
			{
				cout << "HttpClient Cookie" << endl; 
			};
			static shared_ptr<HttpClient> getInstance(void);

			void test(void)
			{
				cout << "Test Http Client, Reference " << to_string(_httpClient.use_count()) << endl;
			}

			~HttpClient(){ cout << "~HttpClient" << endl; }

			HttpResponse execute(HttpRequest request);		

			int32_t enqueue(HttpRequest request, shared_ptr<HttpCallback> callback);
		private:
			string _cacheDir;
			uint32_t cacheSize;
			static weak_ptr<HttpClient> _httpClient;

			HttpClient(const HttpClient &) = delete;
			const HttpClient &operator =(const HttpClient &) = delete;

			HttpConnectionPool _connectionPool;

			HttpRequest followUp(HttpResponse response);
			HttpResponse retryAndFollowInterceptor(HttpRequest request);
			HttpResponse BridgeInterceptor(HttpRequest request);
			HttpResponse CacheInterceptor(HttpRequest request);
			HttpResponse ConnectionInterceptor(HttpRequest request);
			HttpResponse NetworkInterceptor(HttpRequest request, shared_ptr<HttpConnection> connection);


		};
	}
}
#endif
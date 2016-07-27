#ifndef _CPP_NET_HTTP_REQUEST_H_
#define _CPP_NET_HTTP_REQUEST_H_

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <list>
#include <memory>

#include <cpp/net/HttpUrl.h>
#include <cpp/net/HttpHeader.h>
#include <cpp/net/HttpRequestBody.h>

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpRequest
		{
		public:
			HttpRequest(){};
			~HttpRequest(){};

			HttpRequest(string url)
			{				
				_httpUrl = HttpUrl::parse(url);
			}

			HttpHeader& header(void)
			{
				return _httpHeader;
			}

			HttpUrl& url(void)
			{
				return _httpUrl;
			};

			bool needFollow(void)
			{
				return _follow;
			}

			void follow(bool f)
			{
				_follow = f;
			}

			string toString(void)
			{
				string s;
				s.append("URL: "+_httpUrl.toString()).append("\r\n");
				s.append("Header: "+_httpHeader.toString()).append("\r\n");
				s.append("RequestBody: "+_httpRequestBody.toString()).append("\r\n");
				return s;
			}

		private:
			HttpUrl _httpUrl;
			HttpHeader _httpHeader;
			HttpRequestBody _httpRequestBody;
			string _method;			
			bool _follow;
		};
	}
}

#endif
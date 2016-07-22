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

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpRequest
		{
		public:
			HttpRequest();
			~HttpRequest();

		private:
			HttpUrl _httpUrl;
			string _method;			
		};
	}
}

#endif
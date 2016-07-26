#ifndef _CPP_NET_HTTP_RESPONSE_H_
#define _CPP_NET_HTTP_RESPONSE_H_


#include <iostream>
#include <cpp/net/HttpHeader.h>
#include <cpp/net/HttpResponseBody.h>
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpResponse{
		public:
			bool isSuccess(void){ return _success; }
			HttpResponseBody body(void);
			HttpHeader head(void);

		private:
			HttpHeader _httpHeader;
			HttpResponseBody _responseBody;
			bool _success;
		};
	}
}
#endif
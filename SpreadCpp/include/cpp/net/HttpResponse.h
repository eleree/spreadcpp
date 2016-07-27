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
			enum {
				SUCCESS = 0,
				TIMEOUT,
				ROUTE_FAIL,
				CONNECT_FAIL,
				FOLLOW_OVERFLOW,
			};

			bool isSuccess(void){ return _success; }
			HttpResponseBody body(void)
			{
				return _responseBody;
			}

			HttpHeader head(void){
				return _httpHeader;
			}

			void setSuccessStatus(bool isSuccess){
				_success = isSuccess;
			}

			void status(int32_t status)
			{
				_status = status;
			}

			int32_t status(void)
			{
				return _status;
			}

		private:
			int32_t _status;
			HttpHeader _httpHeader;
			HttpResponseBody _responseBody;
			bool _success;
		};
	}
}
#endif
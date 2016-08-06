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

			HttpHeader& header(void){
				return _httpHeader;
			}

			void setSuccessStatus(bool isSuccess){
				_success = isSuccess;
			}

			void status(int32_t status)
			{
				_httpStatus = status;
			}

			int32_t status(void)
			{
				return _httpStatus;
			}

			string toString(void)
			{
				return _httpHeader.toString();
			}

		private:
			int32_t _httpVersion;
			int32_t _httpStatus;
			HttpHeader _httpHeader;
			HttpResponseBody _responseBody;
			bool _success;
		};
	}
}
#endif
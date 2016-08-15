#ifndef _CPP_NET_HTTP_RESPONSE_H_
#define _CPP_NET_HTTP_RESPONSE_H_

#include <memory>
#include <iostream>
#include <cpp/net/HttpHeader.h>
#include <cpp/net/HttpStatus.h>
#include <cpp/net/HttpResponseBody.h>
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpResponse{
		public:
			enum {
				SUCCESS = 0,
				TIMEOUT,
				NO_VALID_CONNECTION,
				ROUTE_FAIL,
				CONNECT_FAIL,
				FOLLOW_OVERFLOW,
			};
			
			bool isSuccess(void)
			{ 
				return _success; 
			}

			shared_ptr<HttpResponseBody> body(void)
			{
				return _responseBody;
			}

			void body(shared_ptr<HttpResponseBody> responseBody)
			{
				_responseBody = responseBody;
			}

			HttpHeader& header(void){
				return _httpHeader;
			}

			void setSuccessStatus(bool isSuccess){
				_success = isSuccess;
			}

			int32_t httpStatus()
			{
				return _httpStatus;
			}

			void httpStatus(int32_t status)
			{
				_httpStatus = status;
			}

			int32_t status(void)
			{
				return _status;
			}

			void status(int32_t status)
			{
				_status = status;
			}

			string toString(void)
			{
				return _httpHeader.toString();
			}

		private:
			int32_t _status; // Response Self Status
			int32_t _httpVersion; // Normal Http Response Status
			int32_t _httpStatus;
			HttpHeader _httpHeader;
			//HttpResponseBody _responseBody;
			shared_ptr<HttpResponseBody> _responseBody;
			bool _success;
		};
	}
}
#endif
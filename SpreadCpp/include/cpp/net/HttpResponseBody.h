#ifndef _CPP_NET_HTTP_RESPONSE_BODY_H_
#define _CPP_NET_HTTP_RESPONSE_BODY_H_

#include <memory>
#include <cpp/net/Socket.h>
#include <cpp/net/HttpConnection.h>

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpResponseBody{
		public:
			HttpResponseBody() : _connection(nullptr), _contentLength(0)
			{}

			void init(int32_t contentType, int32_t contentLength, shared_ptr<HttpConnection> connection)
			{
				_contentType = contentType;
				_contentLength = contentLength;
				_connection = connection;
			}

			void close(void)
			{				
				_connection->release();
				_connection = nullptr;
			}

			string bytes(void)
			{
				if (_connection == nullptr || _contentLength <= 0)
					return "";
				return "Mock Result"; 
			};

			string toString(void)
			{
				string s;
				char streamBuf[512];
				if (_connection == nullptr || _contentLength <= 0)
					return "";
				while (_connection->read(streamBuf, 512) > 0)
				{
					s.append(string(streamBuf));
					cout << string(streamBuf) << endl;
					memset(streamBuf, 0, 512);
				}
				return s;
			};

		private:
			int32_t _contentType;
			int32_t _contentLength;
			shared_ptr<HttpConnection> _connection;
			shared_ptr<Socket> _socket;
		};
	}
}
#endif
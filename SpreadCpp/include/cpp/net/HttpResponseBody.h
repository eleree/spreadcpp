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
			enum{
				RESPONSE_BODY_FIX_LENGTH = 0,
				RESPONSE_BODY_CHUNKED,
				RESPONSE_BODY_UNKNOWN,
			};

			HttpResponseBody() : _connection(nullptr), _contentLength(0)
			{}
		
			HttpResponseBody(int32_t contentType, int32_t contentLength,int32_t connectionType,shared_ptr<HttpConnection> connection)
			{
				_contentType = contentType;
				_contentLength = contentLength;
				_connectionType = connectionType;
				_connection = connection;
			}

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

			string chunkedLengthBody(void)
			{
				string s;
				string rawResponse = "";
				while(1){
					int32_t chunkLength = 0;
					/* hexadecimal number \r\n */
					rawResponse = _connection->readline();
					if ((rawResponse.compare("0") == 0))
						break;
					chunkLength = std::stoi(rawResponse,0,16);
					if (chunkLength <= 0)
						return s;

					/* a chunk of data of the given size */
					rawResponse = _connection->readline();
					if (chunkLength != rawResponse.size())
						return s;

					s.append(rawResponse);					

					if (rawResponse.compare("") == 0)
						break;
				}
				rawResponse = _connection->readline();
				if (rawResponse.compare("") != 0)
					cout << "Not Endof Http Stream?" << endl;
				return s;
			}

			string unknownLengthBody(void)
			{
				string s;
				char streamBuf[512];
				while (_connection->read(streamBuf, 512) > 0)
				{
					s.append(string(streamBuf));
					cout << string(streamBuf) << endl;
					memset(streamBuf, 0, 512);
				}
				return s;
			}

			string fixLengthBody(void)
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

				_connection->release();

				return s;
			}

			string toString(void)
			{
			
				if (_connection == nullptr )
					return "";
					
				if (_connectionType == RESPONSE_BODY_FIX_LENGTH)
					return fixLengthBody();

				if (_connectionType == RESPONSE_BODY_CHUNKED)
					return chunkedLengthBody();

				if (_connectionType == RESPONSE_BODY_UNKNOWN)
					return unknownLengthBody();

				_connection->release();

				return "";			
			};

		private:
			int32_t _contentType;
			int32_t _contentLength;
			int32_t _connectionType;
			shared_ptr<HttpConnection> _connection;
			shared_ptr<Socket> _socket;
		};
	}
}
#endif
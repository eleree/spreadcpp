#ifndef _CPP_NET_HTTP_CONNECTION_H_
#define _CPP_NET_HTTP_CONNECTION_H_

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <list>
#include <memory>
#include <mutex>

#include <cpp/net/Socket.h>
#include <cpp/net/SSLSocket.h>

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpConnection{
		#define HTTP_CONNECTION_MAX_BUFFER_SIZE	512
		public:
						
			HttpConnection() {
				_socket = nullptr;
				_idle = true;
				_buffer = std::make_unique<char[]>(HTTP_CONNECTION_MAX_BUFFER_SIZE);
			}

			~HttpConnection() {}

			bool idle(void);
			void acquire(void);
			void release(void);

			string address(void);
			void setAddress(string scheme, string address, uint16_t port);

			int32_t connectSocket(int32_t connectTimeout, int32_t readTimeout);
			int32_t connectSSLScoket(int32_t connectTimeout, int32_t readTimeout);

			/* stream operations */
			
			int32_t available(void);
			int32_t read(char * buf, int32_t len);
			int32_t read(char * buf, int32_t len, int32_t offset);			
			int32_t skip(int32_t len);
			string readline();
			int32_t write(char * buf, int32_t len);

			bool sameAddress(string address);
			bool sameScheme(string scheme);

		private:
			bool _idle;			
			std::mutex _mutex;
			int32_t _type; // socket or ssl socket
			string _scheme; // which scheme this connection connects to
			string _address; // which address this connection connects to
			uint16_t _port;
			uint64_t _expireTime; 
			shared_ptr<Socket> _socket;
			shared_ptr<SSLSocket> _sslSocket;
			unique_ptr<char[]> _buffer = nullptr;
		};
	}
}
#endif
#ifndef _CPP_NET_SOCKET_H_
#define _CPP_NET_SOCKET_H_

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <list>
#include <memory>
#if defined(_WIN32) ||  defined(_WIN64)
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#endif

using namespace std;
namespace cpp{
	namespace net{
		class Socket{
		public:
			Socket();
			Socket(string host, uint16_t port);
			~Socket();
			int32_t connect(void);
			int32_t connect(string host, uint16_t port);
			int32_t send(char * sendBuf, uint32_t sendSize);
			int32_t recv(char * recvBuf, uint32_t recvLen);
			int32_t close();
			int32_t shutdownInput();
			int32_t shutdownOutput();

			bool isConnected(void);
			bool isClosed(void);
			bool isInputShutdown(void);
			bool isOutputShutdown(void);

			string toString(void);

		private:
			string _host;
			uint16_t _port;

#if defined(_WIN32) ||  defined(_WIN64)
			static bool _init;
			WSADATA _wsaData;
			SOCKET _socket = INVALID_SOCKET;
#endif
		};
	}
}

#endif
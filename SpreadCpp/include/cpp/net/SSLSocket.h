#ifndef _CPP_NET_SSL_SOCKET_H_
#define _CPP_NET_SSL_SOCKET_H_

#define WIN32_LEAN_AND_MEAN 
#if defined(_WIN32) ||  defined(_WIN64)
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#endif

#include <iostream>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

//Download OpenSSL from http://www.npcglib.org/~stathis/downloads/openssl-1.0.1t-vs2013.7z
namespace cpp{
	namespace net{
		class SSLSocket{
		public:
#define CHK_NULL(x) if ((x)==NULL) exit (1)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(2); }

			SSLSocket();
			~SSLSocket();

			int32_t connect(void);
			int32_t connect(string host, uint16_t port);
			int32_t connect(string host, uint16_t port, uint32_t timeout);

		private:			
			SOCKET sd;
			SSL* ssl = NULL;
			SSL_METHOD *meth;
			X509* scert = NULL;
			SSL_CTX *ctx = NULL;

			string _host;
			uint16_t _port;
			uint32_t _timeout;
			bool _isClosed;
			bool _isConnected;
			bool _isInputShutdown;
			bool _isOutputShutdown;
#if defined(_WIN32) ||  defined(_WIN64)
			SOCKET _socket = INVALID_SOCKET;
#endif
		};
	}
}
#endif

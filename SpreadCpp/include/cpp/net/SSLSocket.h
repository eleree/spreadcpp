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
#pragma warning(disable:4996)
#endif

#include <iostream>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <memory>
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <cpp/net/HttpTlsVersion.h>
using namespace std;

//Download OpenSSL from http://www.npcglib.org/~stathis/downloads/openssl-1.0.1t-vs2013.7z
namespace cpp{
	namespace net{
		class SSLSocket{
		public:
#define CHK_NULL(x) if ((x)==NULL) exit (1)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s);  }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); }

			SSLSocket();
			SSLSocket(string method);
			~SSLSocket();

			int32_t connect(string host, uint16_t port);
			int32_t connect(string host, uint16_t port, uint32_t timeout);
			int32_t connect(string host, uint16_t port, int32_t cipherSuite, uint32_t timeout);
			int32_t send(char * sendBuf, uint32_t sendSize);
			int32_t recv(char * recvBuf, uint32_t recvLen);

			X509* peerCertificate(void);
			string peerCertificateString(void);
			string peerCertificateSubjectName(void);
			string peerCertificateIssuerName(void);
			string cipherSuite(void);
			bool isEncrypted(void);

			int32_t close();
			int32_t shutdownInput();
			int32_t shutdownOutput();
		private:			
			SSL* _ssl = NULL;
			SSL_METHOD *meth;
			SSL_CTX *ctx = NULL;
			X509* _peerCertificate = NULL;
			string _cipherSuite;

			string _host;
			uint16_t _port;
			uint32_t _timeout;
			bool _isClosed;
			bool _isEncrypted;
			bool _isConnected;
			bool _isInputShutdown;
			bool _isOutputShutdown;
#if defined(_WIN32) ||  defined(_WIN64)
			SOCKET _socket = INVALID_SOCKET;
#endif
			int32_t _connectSSLSocket(void);
			SSL_METHOD * _makeCipher;
		};
	}
}
#endif

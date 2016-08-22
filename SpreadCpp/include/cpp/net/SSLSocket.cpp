#include <cpp/net/SSLSocket.h>

using namespace cpp::net;

SSLSocket::SSLSocket()
{
	SSLeay_add_ssl_algorithms();
	meth = (SSL_METHOD*)SSLv23_client_method();
	ERR_print_errors_fp(stderr);
	SSL_load_error_strings();
	if (meth == NULL)
	{
		cout << "Meth is Null" << endl;
	}
	ctx = SSL_CTX_new(meth);
	if (ctx == NULL)
	{
		cout << "New SSL context fail" << endl;;
		ERR_print_errors_fp(stderr);
		return;
	}

	cout << "Create SSL Socket 2" << endl;
}

SSLSocket::~SSLSocket()
{
	if (_socket != INVALID_SOCKET)
		closesocket(_socket);

	if (_ssl != NULL)
		SSL_free(_ssl);

	if (ctx != NULL)		
		SSL_CTX_free(ctx);
}

int32_t SSLSocket::connect(void)
{
	return 0;
}

int32_t SSLSocket::connect(string host, uint16_t port)
{
	return connect(host, port, 5000);
}

int32_t SSLSocket::connect(string host, uint16_t port, uint32_t timeout)
{
	int32_t error = 0;
	char* txt = NULL;
	_host = host;
	_port = port;
	_timeout = timeout;
	int32_t rc = -1;
	struct addrinfo hints;
	struct addrinfo *result = NULL;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (_host.empty() || _port == 0)
		return rc;
	if (inet_addr(_host.c_str()) == INADDR_NONE)
		return rc;

	cout << "Start Connect" << endl;
	//rc = getaddrinfo(_host.c_str(), to_string(_port).c_str(), &hints, &result);
	_socket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
	if (_socket == INVALID_SOCKET)
	{
		cout << "Invalid Socket" << endl;
		return -2;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(_host.c_str());
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(_port);

	// If iMode = 0, blocking is enabled; 
	// If iMode != 0, non-blocking mode is enabled.
	u_long iMode = 1;
	ioctlsocket(_socket, FIONBIO, (u_long FAR*)&iMode);
	rc = ::connect(_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	//rc = ::connect(_socket, result->ai_addr, (int)result->ai_addrlen);

	if (rc != NO_ERROR)
	{
		cout << "Start Select" << endl;
		struct timeval tm;
		tm.tv_sec = _timeout / 1000;
		tm.tv_usec = _timeout % 1000 * 1000;
		int ret = -1;

		fd_set set;
		FD_ZERO(&set);
		FD_SET(_socket, &set);
		if (select(-1, NULL, &set, NULL, &tm) <= 0)
		{
			closesocket(_socket);
			cout << "Invalid Socket" << endl;
			_socket = INVALID_SOCKET;
		}
		else{
			int error = -1;
			int optLen = sizeof(int);
			getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char*)&error, &optLen);
			if (0 != error)
			{
				rc = -1;
				closesocket(_socket);
				cout << "Invalid Socket" << endl;
				_socket = INVALID_SOCKET;
			}
			else{
				cout << "Socket Connected" << endl;
				u_long iMode = 0;
				ioctlsocket(_socket, FIONBIO, (u_long FAR*)&iMode);
				_ssl = SSL_new(ctx); 
				if (_ssl == NULL)
				{
					cout << "SSL New Fail " << endl;
					return -1;
				}
				
				SSL_set_fd(_ssl, _socket);
				error = SSL_connect(_ssl); 

				if (error == -1)
				{
					ERR_print_errors_fp(stderr);
					return -1;
				}

				CHK_SSL(error);
				printf("SSL connection using %s\n", SSL_get_cipher(_ssl));
				/* Get Server certificate - optional */

				scert = SSL_get_peer_certificate(_ssl); 
				CHK_NULL(scert);
				printf("Server Certificate:\n");

				txt = X509_NAME_oneline(X509_get_subject_name(scert), 0, 0);
				CHK_NULL(txt);
				printf("Subject: %s\n", txt);
				OPENSSL_free(txt);

				txt = X509_NAME_oneline(X509_get_issuer_name(scert), 0, 0);
				CHK_NULL(txt);
				printf("Issuer: %s\n", txt);
				OPENSSL_free(txt);

				/* Here we can check what we wanted about the Server certificate */

				X509_free(scert);
				rc = 0;
			}
		}
	}

	if (result != NULL)
	freeaddrinfo(result);

	return rc;
}


int32_t SSLSocket::send(char * sendBuf, uint32_t sendSize)
{
	if (_socket == INVALID_SOCKET || _ssl == NULL)
		return -1;
	return 	SSL_write(_ssl, sendBuf, sendSize);
}

int32_t SSLSocket::recv(char * recvBuf, uint32_t recvLen)
{
	if (_socket == INVALID_SOCKET || _ssl == NULL)
		return -1;
	return SSL_read(_ssl, recvBuf, recvLen);
}

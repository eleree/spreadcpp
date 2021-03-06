#include <cpp/net/SSLSocket.h>

using namespace std;
using namespace cpp::net;

SSLSocket::SSLSocket(string method)
{

	/* Need to be replace by openssl method factory */
	meth = (SSL_METHOD*)HttpTlsVersion::tlsVersion(method);
	if (meth == NULL)
	{
		cout << "Request method is not Support" << endl;
		ERR_print_errors_fp(stderr);
		return;
	}
	ctx = SSL_CTX_new(meth);
	if (ctx == NULL)
	{
		cout << "New SSL context fail" << endl;;
		ERR_print_errors_fp(stderr);
		return;
	}
}

SSLSocket::SSLSocket()
{
	for (auto && x : HttpTlsVersion::supportTlsVersion())
		cout << x << endl;
	meth = (SSL_METHOD*)SSLv23_client_method();
	if (meth == NULL)
	{
		cout << "Meth is Null" << endl;
		ERR_print_errors_fp(stderr);
	}
	ctx = SSL_CTX_new(meth);
	if (ctx == NULL)
	{
		cout << "New SSL context fail" << endl;;
		ERR_print_errors_fp(stderr);
		return;
	}
}

SSLSocket::~SSLSocket()
{
	
	if (_peerCertificate != NULL)
		X509_free(_peerCertificate);

	if (_ssl != NULL)
		SSL_free(_ssl);

	if (_socket != INVALID_SOCKET)
		closesocket(_socket);

	if (ctx != NULL)		
		SSL_CTX_free(ctx);
}

int32_t SSLSocket::connect(string host, uint16_t port)
{
	return connect(host, port, 5000);
}

int32_t SSLSocket::connect(string host, uint16_t port, uint32_t timeout)
{
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
		struct timeval tm;
		tm.tv_sec = _timeout / 1000;
		tm.tv_usec = _timeout % 1000 * 1000;

		fd_set set;
		FD_ZERO(&set);
		FD_SET(_socket, &set);
		if (select(-1, NULL, &set, NULL, &tm) <= 0)
		{
			closesocket(_socket);
			rc = -1;
			cout << "Invalid Socket" << endl;
			_socket = INVALID_SOCKET;
		}else{
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
				_isConnected = true;
				rc = _connectSSLSocket();
			}
		}
	}

	if (result != NULL)
		freeaddrinfo(result);

	return rc;
}


int32_t SSLSocket::close()
{
	_isOutputShutdown = true;
	_isInputShutdown = true;
	_isClosed = true;

#if defined(_WIN32) ||  defined(_WIN64)
	return closesocket(_socket);
#endif
}

int32_t SSLSocket::shutdownInput()
{
	_isInputShutdown = true;
#if defined(_WIN32) ||  defined(_WIN64)
	return shutdown(_socket, SD_RECEIVE);
#endif
}

int32_t SSLSocket::shutdownOutput()
{
	_isOutputShutdown = true;
#if defined(_WIN32) ||  defined(_WIN64)
	return shutdown(_socket, SD_SEND);
#endif
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

int32_t SSLSocket::_connectSSLSocket(void)
{
	int32_t error = 0;

	if (_isConnected != true || _isEncrypted == true )
		return -1;

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
		SSL_free(_ssl);
		_ssl = NULL;
		return -1;
	}

	_isEncrypted = true;
	_cipherSuite = string(SSL_get_cipher(_ssl));
	_peerCertificate = SSL_get_peer_certificate(_ssl);
	
	return error;
}

string SSLSocket::cipherSuite(void)
{
	if (_isEncrypted != true || _socket == INVALID_SOCKET)
		return "";
	return _cipherSuite;
}

X509* SSLSocket::peerCertificate(void)
{
	if (_isEncrypted != true || _socket == INVALID_SOCKET )
		return NULL;
	return _peerCertificate;
}

string SSLSocket::peerCertificateString(void)
{
	char buffer[512] = {0};
	int32_t bufferLen = 0;
	string certificateString;
	if ( _isEncrypted != true || _socket == INVALID_SOCKET || \
			_peerCertificate == NULL)
		return "";

	BIO *mem = BIO_new(BIO_s_mem());
	X509_print(mem, _peerCertificate);
	while (1)
	{
		bufferLen = BIO_gets(mem, (char*) buffer, 512);
		if (bufferLen <= 0){
			break;
		}
		certificateString.append(string(buffer));
	}
	BIO_free(mem);

	return certificateString;
}

string SSLSocket::peerCertificateSubjectName(void)
{
	char* name = NULL;
	string subjectName;

	if (_isEncrypted != true || _socket == INVALID_SOCKET || \
		_peerCertificate == NULL)
		return "";

	name = X509_NAME_oneline(X509_get_subject_name(_peerCertificate), 0, 0);
	if (name == NULL)
		return "";
	subjectName = string(name);

	OPENSSL_free(name);
	return subjectName;
}

string SSLSocket::peerCertificateIssuerName(void)
{
	char* name = NULL;
	string issuerName;

	if (_isEncrypted != true || _socket == INVALID_SOCKET || \
		_peerCertificate == NULL)
		return "";

	name = X509_NAME_oneline(X509_get_issuer_name(_peerCertificate), 0, 0);
	if (name == NULL)
		return "";
	issuerName = string(name);

	OPENSSL_free(name);
	return issuerName;
}
#include <cpp/net/Socket.h>

using namespace cpp::net;

bool Socket::_init = false;

Socket::Socket() : _timeout(10000)
{
	_isOutputShutdown = false;
	_isInputShutdown = false;
	_isClosed = false;
#if defined(_WIN32) ||  defined(_WIN64)
	int result;
	if (_init == false)
	{
		result = WSAStartup(MAKEWORD(2, 2), &_wsaData);
		if (result == 0) {
			_init = true;
		}
	}
#endif
}

Socket::Socket(string host, uint16_t port)
{

}

Socket::~Socket()
{

}

int32_t Socket::connect(void)
{
	int rc = -1;
	struct addrinfo hints;
	struct addrinfo *result = NULL;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (_host.empty() || _port == 0)
		return rc;
	rc = getaddrinfo(_host.c_str(), to_string(_port).c_str(), &hints, &result);
	_socket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
	if (_socket == INVALID_SOCKET)
	{
		cout << "Invalid Socket" << endl;
		return -2;
	}
	
	rc = ::connect(_socket, result->ai_addr, (int)result->ai_addrlen);
	if (rc == SOCKET_ERROR)
	{
		closesocket(_socket);
		cout << "Invalid Socket" << endl;
		_socket = INVALID_SOCKET;
	}

	freeaddrinfo(result);
	return rc;
}

int32_t Socket::connect(string host, uint16_t port)
{
	_host = host;
	_port = port;
	return Socket::connect(_host,_port,_timeout);
}

int32_t Socket::connect(string host, uint16_t port, uint32_t timeout)
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
		tm.tv_sec = _timeout/1000;
		tm.tv_usec = _timeout%1000*1000;
		int ret = -1;

		fd_set set;
		FD_ZERO(&set);
		FD_SET(_socket, &set);
		if (select(-1, NULL, &set, NULL, &tm) <= 0)
		{
			closesocket(_socket);
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
			}else{
				cout << "Socket Connected" << endl;
				u_long iMode = 0;
				ioctlsocket(_socket, FIONBIO, (u_long FAR*)&iMode);
				rc = 0;
			}			
		}
	}

	if (result != NULL)
		freeaddrinfo(result);

	return rc;
}



int32_t Socket::send(char * sendBuf, uint32_t sendSize)
{
	if (_socket == INVALID_SOCKET)
		return -1;
	return ::send(_socket, sendBuf, sendSize, 0);
}

int32_t Socket::recv(char * recvBuf, uint32_t recvLen)
{
	if (_socket == INVALID_SOCKET)
		return -1;
	return ::recv(_socket, recvBuf, recvLen, 0);
}

string Socket::readline(void)
{
	int rc = 0;
	string line;

	if (_socket == INVALID_SOCKET)
		return "";

	for (;;)
	{
		char c;
		rc = ::recv(_socket, &c, 1, 0);
		if (rc <= 0)
			return line;
		if (c == '\r')
			continue;
		else if (c == '\n')
		{
			return line;
		}else{
			line += c;
		}
	}
}


int32_t Socket::close()
{
	_isOutputShutdown = true;
	_isInputShutdown = true;
	_isClosed = true;

#if defined(_WIN32) ||  defined(_WIN64)
	return closesocket(_socket);
#endif
}

int32_t Socket::shutdownInput()
{
	_isInputShutdown = true;
#if defined(_WIN32) ||  defined(_WIN64)
	return shutdown(_socket, SD_RECEIVE);
#endif
}

int32_t Socket::shutdownOutput()
{
	_isOutputShutdown = true;
#if defined(_WIN32) ||  defined(_WIN64)
	return shutdown(_socket, SD_SEND);
#endif
}


void setReuseAddress(bool on)
{

}

bool getReuseAddress(void)
{
	return true;
}

void setTcpNoDelay(bool on)
{

}

bool getTcpNoDelay(void)
{
	return true;
}

void setKeepAlive(bool on)
{

}

bool getKeepAlive(void)
{
	return true;

}

void setReceiveBufferSize(uint32_t size)
{

}

uint32_t getReceiveBufferSize(void);
void setSendBufferSize(uint32_t size);
uint32_t getSendBufferSize(void);
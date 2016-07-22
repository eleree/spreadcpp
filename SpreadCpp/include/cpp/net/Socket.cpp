#include <cpp/net/Socket.h>

using namespace cpp::net;

bool Socket::_init = false;

Socket::Socket()
{
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
	return rc;
}

int32_t Socket::connect(string host, uint16_t port)
{
	_host = host;
	_port = port;
	return Socket::connect();
}

int32_t Socket::send(char * sendBuf, uint32_t sendSize)
{
	return ::send(_socket, sendBuf, sendSize, 0);
}

int32_t Socket::recv(char * recvBuf, uint32_t recvLen)
{
	return ::recv(_socket, recvBuf, recvLen, 0);
}

int32_t Socket::close()
{
#if defined(_WIN32) ||  defined(_WIN64)
	return closesocket(_socket);
#endif
}

int32_t Socket::shutdownInput()
{
#if defined(_WIN32) ||  defined(_WIN64)
	return shutdown(_socket, SD_RECEIVE);
#endif
}

int32_t Socket::shutdownOutput()
{
#if defined(_WIN32) ||  defined(_WIN64)
	return shutdown(_socket, SD_SEND);
#endif
}
#include <cpp/net/HttpConnection.h>

int32_t HttpConnection::connectSocket(int32_t connectTimeout, int32_t readTimeout)
{
	if (_socket == nullptr)
		_socket = make_shared<Socket>();
	_socket->connect(_address, _port, connectTimeout);
	return 0;
}

int32_t HttpConnection::connectSSLScoket(int32_t connectTimeout, int32_t readTimeout)
{
	return 0;
}

string HttpConnection::address(void)
{
	return _address;
}

bool HttpConnection::idle(void)
{
	return _idle;
}

int32_t HttpConnection::available(void)
{
	return 0;
}

int32_t HttpConnection::read(char * buf, int32_t len)
{
	if (_socket == nullptr)
		return -1;

	return _socket->recv(buf, len);;
}

int32_t HttpConnection::read(char * buf, int32_t len, int32_t offset)
{
	if (_socket == nullptr)
		return -1;
	return _socket->recv(buf, len);
}

int32_t HttpConnection::skip(int32_t len)
{
	return 0;
}

string HttpConnection::readline()
{
	int rc = 0;
	string line;

	if (_socket == nullptr)
		return "";

	for (;;)
	{
		char c;
		rc = _socket->recv(&c, 1);
		if (rc <= 0)
			return line;
		if (c == '\r')
			continue;
		else if (c == '\n')
		{
			return line;
		}
		else{
			line += c;
		}
	}
	return ""; 
}

int32_t HttpConnection::write(char * buf, int32_t len)
{
	if (_socket == nullptr)
		return -1;
	return _socket->send(buf, len);
}

bool HttpConnection::sameAddress(string address)
{
	return _address.compare(address) == 0;	
}

void HttpConnection::acquire(void)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_idle = false;
}

void HttpConnection::release(void)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_idle = true;
}

void HttpConnection::setAddress(string address, uint16_t port)
{
	_address = address;
	_port = port;
}

#include <cpp/net/HttpConnection.h>

int32_t HttpConnection::available(void)
{
	return 0;
}

int32_t HttpConnection::read(char * buf, int32_t len)
{
	return 0;
}

int32_t HttpConnection::read(char * buf, int32_t len, int32_t offset)
{
	return 0;
}

int32_t skip(int32_t len)
{
	return 0;
}

string readline()
{
	return ""; 
}

int32_t write(char * buf, int32_t len)
{
	return 0;
}

bool compareDomain(string host)
{
	return false;
}
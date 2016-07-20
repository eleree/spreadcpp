#include <cpp/net/HttpUrl.h>

using namespace cpp::net;


HttpUrl::HttpUrl() :_scheme("http"), _username(""), _password("")
{

}

HttpUrl::HttpUrl(string url)
{

}

string HttpUrl::scheme(void)
{
	return _scheme;
}

HttpUrl& HttpUrl::scheme(string scheme)
{
	_scheme = scheme;
	return *this;
}

string HttpUrl::username(void)
{
	return _username;
}

HttpUrl& HttpUrl::username(string username)
{
	_username = username;
	return *this;
}
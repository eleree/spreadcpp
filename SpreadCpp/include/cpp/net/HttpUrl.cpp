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

string HttpUrl::password(void)
{
	return _password;
}

HttpUrl& HttpUrl::password(string password)
{
	_password = password;
	return *this;
}

string HttpUrl::host(void)
{
	return _host;
}

HttpUrl& HttpUrl::host(string host)
{
	_host = host;
	return *this;
}

string HttpUrl::toString(void)
{
	string url;
	url.append(_scheme);
	url.append("://");
	if ( ! _username.empty() || ! _password.empty())
	{
		url.append(_username);
		if ( ! _password.empty())
		{
			url.append(":");
			url.append(_password);
		}
		url.append("@");
	}
	
	url.append(_host);
	return url;
}


HttpUrl HttpUrl::parse(string url)
{
	HttpUrl httpUrl;
	httpUrl.scheme("http").host("www.qq.com");
	return std::move(httpUrl);
}

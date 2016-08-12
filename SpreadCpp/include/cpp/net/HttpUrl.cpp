#include <cpp/lang/String.h>
#include <cpp/net/HttpUrl.h>

using namespace cpp::net;
using namespace cpp::lang;

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


uint16_t HttpUrl::port()
{
	return _port;
}

HttpUrl& HttpUrl::port(uint16_t port)
{
	_port = port;
	return *this;
};

string HttpUrl::fragment(void)
{
	return _fragment;
}

HttpUrl& HttpUrl::fragment(string fragment)
{
	_fragment = fragment;
	return *this;
}

list<string> HttpUrl::path(void)
{
	return _pathList;
}

string HttpUrl::pathString(void)
{
	string s="/";
	for (auto &p : _pathList)
	{
		s.append(p);		
	}
	return s;
}

int32_t HttpUrl::addPath(string path)
{
	_pathList.push_back(path);
	return 0;
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
	uint32_t startPos = HttpUrl::skipLeadingSpace(url, 0, url.length());
	uint32_t limitPos = HttpUrl::skipTrailingSpace(url, startPos, url.length());
	
	if (String::regionMatches(url, startPos, string("http:"), 0, 5) == true)
	{
		httpUrl.scheme("http");
		httpUrl.port(80);
	}else if (String::regionMatches(url, startPos, string("https:"), 0, 6) == true)
	{
		httpUrl.scheme("https");
		httpUrl.port(433);
	}

	/* host */
	url = String::substring(url, startPos, limitPos);
	cout << "Host:" + url << endl;
	int32_t hostEnd = String::indexOf(url, '/', httpUrl.scheme().size() + 3);
	int32_t hostStart = String::indexOf(url, '/', httpUrl.scheme().size() + 2) + 1;

	if (hostEnd < 0)
	{
		httpUrl.host(String::substring(url, hostStart));
		return httpUrl;
	}
	else
		httpUrl.host(String::substring(url,hostStart,hostEnd));
	
	/* path */
	url = String::substring(url, hostEnd);
	cout << "Path:" + url << endl;
	uint32_t slashIndex = 0;
	for (;;)
	{
		int32_t firstSlash = String::indexOf(url, '/', slashIndex);
		int32_t secondSlash = String::indexOf(url, '/', slashIndex+1);
		if (secondSlash < 0)
		{
			int32_t endPath = HttpUrl::delimiterOffset(url, firstSlash, url.size() - firstSlash, "#?");
			if (endPath < 0)
			{
				cout << String::substring(url, firstSlash + 1) << endl;
				httpUrl.addPath(String::substring(url, firstSlash + 1));
				return httpUrl;
			}else{
				cout << String::substring(url, firstSlash + 1, endPath) << endl;
				httpUrl.addPath(String::substring(url, firstSlash + 1, endPath));
				url = String::substring(url, endPath);
			}
			break;
		}
		cout << String::substring(url, firstSlash + 1, secondSlash) << endl;
		httpUrl.addPath(String::substring(url, firstSlash + 1, secondSlash));
		slashIndex = secondSlash;
	}
	
	/* query */
	cout << "Query:" << url << endl;
	int32_t andTokenIndex = 0;
	int32_t queryStart = 1;
	int32_t numberSignIndex = 0;
	for (;;)
	{
		andTokenIndex = String::indexOf(url, '&', queryStart);
		if (andTokenIndex < 0)
		{
			numberSignIndex = HttpUrl::delimiterOffset(url, queryStart, url.size() - queryStart, "#");
			if (numberSignIndex < 0)
			{
				cout << String::substring(url, queryStart) << endl;
			}
			else
			{
				cout << String::substring(url, queryStart, numberSignIndex) << endl;
				url = String::substring(url, numberSignIndex);
			}
			break;
		}
		cout << String::substring(url, queryStart, andTokenIndex) << endl;
		queryStart = andTokenIndex + 1;
	}

	// fragment
	cout << "Fragment:" + url << endl;
	httpUrl.fragment(String::substring(url, 1));

	return std::move(httpUrl);
}

uint32_t HttpUrl::skipLeadingSpace(string s, uint32_t pos, uint32_t limit)
{
	for (uint32_t i = pos; i < limit; i++) {
		switch (String::charAt(s,i)) {
		case '\t':
		case '\n':
		case '\f':
		case '\r':
		case ' ':
			continue;
		default:
			return i;
		}
	}
	return limit;
}


uint32_t HttpUrl::skipTrailingSpace(string s, uint32_t pos, uint32_t limit)
{
	for (uint32_t i = limit - 1; i >= pos; i--) {
		switch (String::charAt(s, i)) {
		case '\t':
		case '\n':
		case '\f':
		case '\r':
		case ' ':
			continue;
		default:
			return i + 1;
		}
	}
	return pos;
}

int32_t HttpUrl::delimiterOffset(string input, int32_t pos, int32_t limit, string delimiters)
{
	for (int i = pos; i < limit; i++) {
		if (String::indexOf(delimiters, String::charAt(input,i)) != -1) return i;
	}
	return limit;
}
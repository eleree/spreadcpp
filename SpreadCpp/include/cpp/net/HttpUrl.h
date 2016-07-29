#ifndef _CPP_NET_HTTP_URL_H_
#define _CPP_NET_HTTP_URL_H_

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <list>
#include <memory>

using namespace std;
namespace cpp{
	namespace net{
		class HttpUrl{
		public:

			HttpUrl();
			HttpUrl(string url);
			
			~HttpUrl(){ cout << "Relase HttpUrl Object" << endl; }

			string scheme(void);
			HttpUrl& scheme(string scheme);

			string username(void);
			HttpUrl& username(string username);

			string password(void);
			HttpUrl& password(string password);

			string host(void);
			HttpUrl& host(string host);

			uint16_t port();
			HttpUrl& port(uint16_t port);

			string fragment(void)
			{
				return _fragment;
			}

			HttpUrl& fragment(string fragment)
			{
				_fragment = fragment;
				return *this;
			}

			list<string> path(void)
			{
				return _pathList;
			}

			int32_t addPath(string path)
			{
				_pathList.push_back(path);
				return 0;
			}

			list<string> query(void);
			HttpUrl& addQuery(string name, string value);

			list<string> encodedPath(void);
			list<string> encodedQuery(void);

			string toString(void);

			static HttpUrl parse(string url);
		private:
			string pathEncodeSet = " \"<>^`{}|/\\?#";

			string _scheme = "http";
			string _username;
			string _password;
			string _host;
			uint16_t _port;
			string _fragment;

			list<string> _pathList;
			list<string> _queryList;

			static uint32_t skipLeadingSpace(string s, uint32_t pos, uint32_t limit);
			static uint32_t skipTrailingSpace(string s, uint32_t pos, uint32_t limit);
			static int32_t delimiterOffset(string input, int32_t pos, int32_t limit, string delimiters);

		};

	}
}
#endif
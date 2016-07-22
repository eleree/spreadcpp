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

			string fragment(void);
			HttpUrl& addFragment(string fragment);

			list<string> path(void);
			int32_t addPath(string path);

			list<string> query(void);
			HttpUrl& addQuery(string name, string value);

			list<string> encodedPath(void);
			list<string> encodedQuery(void);

			string toString(void);
		private:
			const string pathEncodeSet = " \"<>^`{}|/\\?#";

			string _scheme = "http";
			string _username;
			string _password;
			string _host;
			uint16_t _port;
			uint16_t _fragment;

			list<string> _pathList;
			list<string> _queryList;

		};
	}
}
#endif
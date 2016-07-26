#ifndef _CPP_NET_HTTP_CLIENT_H_
#define _CPP_NET_HTTP_CLIENT_H_

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
		class HttpClient{
		public:
			struct ctor_cookie {};
			explicit HttpClient(ctor_cookie) 
			{
				cout << "HttpClient Cookie" << endl; 
			};
			static shared_ptr<HttpClient> getInstance(void);

			void test(void)
			{
				cout << "Test Http Client, Reference " << to_string(_httpClient.use_count()) << endl;
			}

			~HttpClient(){ cout << "~HttpClient" << endl; }
		private:
			static weak_ptr<HttpClient> _httpClient;
		};
	}
}
#endif
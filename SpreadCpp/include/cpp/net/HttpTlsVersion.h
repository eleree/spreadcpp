#ifndef _CPP_NET_HTTP_TLS_VERSION_H_
#define _CPP_NET_HTTP_TLS_VERSION_H_

#include <iostream>
#include <map>
#include <list>
#include <mutex>
#include <openssl/ssl.h>

using namespace std;

namespace cpp{
	namespace net{
		class HttpTlsVersion{
		public:
			enum{
				TLS_1_2 = 0,	// 2008.
				TLS_1_1,		// 2006.
				TLS_1_0,		// 1999.
				SSL_3_0,		// 1996.
			};

			static const SSL_METHOD * tlsVersion(string version)
			{
				std::lock_guard<std::mutex> locker(_mutex);

				if (_methodMap.size() == 0)				
					initMap();
				
				if (_methodMap.find(version) == _methodMap.end())
					return NULL;

				return _methodMap.at(version);
			}

			static list<string> supportTlsVersion(void)
			{
				std::lock_guard<std::mutex> locker(_mutex);
				list<string> supportTlsList;

				if (_methodMap.size() == 0)
					initMap();

				for (auto && tls : _methodMap)
					supportTlsList.push_back(tls.first);

				return supportTlsList;
			}

		private:
			static std::mutex _mutex;
			static map<string, const SSL_METHOD *> _methodMap;

			static void initMap(void)
			{
				_methodMap.insert(make_pair<string, const SSL_METHOD*>(string("SSLv2"), SSLv23_client_method()));
				_methodMap.insert(make_pair<string, const SSL_METHOD*>(string("SSLv3"), SSLv23_client_method()));
				_methodMap.insert(make_pair<string, const SSL_METHOD*>(string("TLSv1"), TLSv1_client_method()));
				_methodMap.insert(make_pair<string, const SSL_METHOD*>(string("TLSv1.1"), TLSv1_1_client_method()));
				_methodMap.insert(make_pair<string, const SSL_METHOD*>(string("TLSv1.2"), TLSv1_2_client_method()));
			}

		};
	}
}

#endif
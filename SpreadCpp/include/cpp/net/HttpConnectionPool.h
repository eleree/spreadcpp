#ifndef _CPP_NET_HTTP_CONNECTION_POOL_H_
#define _CPP_NET_HTTP_CONNECTION_POOL_H_

#include <mutex>
#include <vector>
#include <cpp/net/HttpConnection.h>

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpConnectionPool
		{
		public:
			HttpConnectionPool(){};
			HttpConnectionPool(int32_t maxCount);
			shared_ptr<HttpConnection> findIdleConnection(string scheme, string host);

		private:
			int32_t _maxCount;
			std::mutex _mutex;
			vector<shared_ptr<HttpConnection>> _httpConnectionPool;
		};
	}
}
#endif
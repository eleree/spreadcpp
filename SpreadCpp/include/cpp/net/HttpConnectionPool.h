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
			HttpConnectionPool();
			shared_ptr<HttpConnection> findIdleConnection(string host);

		private:
			int32_t _max;
			std::mutex _mutex;
			vector<shared_ptr<HttpConnection>> _httpConnectionPool;
		};
	}
}
#endif
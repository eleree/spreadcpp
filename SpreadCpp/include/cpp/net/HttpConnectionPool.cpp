#include <cpp/net/HttpConnectionPool.h>

HttpConnectionPool::HttpConnectionPool(int32_t maxCount)
{
	for (int32_t i = 0; i < maxCount; i++)
	{
		_httpConnectionPool.push_back(make_shared<HttpConnection>());
	}
}

shared_ptr<HttpConnection> HttpConnectionPool::findIdleConnection(string host)
{
	std::lock_guard<std::mutex> lock(_mutex);
	for (auto & c : _httpConnectionPool)
	{
		if (c->idle() == true && c->sameAddress(host) == true )
		{
			//Found a connection with same 
			c->acquire();
			return c;			
		}
	}

	for (auto & c : _httpConnectionPool)
	{
		if (c->idle() == true)
		{
			c->acquire();
			return c;
		}
		
	}

	return nullptr;
}

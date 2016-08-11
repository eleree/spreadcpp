#include <cpp/net/HttpConnectionPool.h>

HttpConnectionPool::HttpConnectionPool()
{

}

shared_ptr<HttpConnection> HttpConnectionPool::findIdleConnection(string host)
{
	std::lock_guard<std::mutex> lock(_mutex);
	return nullptr;
}

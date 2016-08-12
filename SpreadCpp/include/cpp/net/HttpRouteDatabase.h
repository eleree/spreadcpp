#ifndef _CPP_NET_HTTP_ROUTE_DATABASE_H_
#define _CPP_NET_HTTP_ROUTE_DATABASE_H_

#include <mutex>
#include <memory>
#include <set>
#include <string>

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpRouteDatabase{
		public:
			void addFailRoute(string host)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				_failRouteSet.insert(host);
			}

			void removedFailroute(string host)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				_failRouteSet.erase(host);
			}

			bool shouldPostpone(string host)
			{
				std::lock_guard<std::mutex> lock(_mutex);
				 return (_failRouteSet.find(host) != _failRouteSet.end());
			}

		private:
			std::mutex _mutex;
			std::set<string> _failRouteSet;
		};		
	}
}
#endif
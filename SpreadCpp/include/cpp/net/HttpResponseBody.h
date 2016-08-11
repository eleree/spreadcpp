#ifndef _CPP_NET_HTTP_RESPONSE_BODY_H_
#define _CPP_NET_HTTP_RESPONSE_BODY_H_

#include <memory>
#include <cpp/net/Socket.h>

using namespace std;
using namespace cpp::net;

namespace cpp{
	namespace net{
		class HttpResponseBody{
		public:
			string bytes(void){ return "Mock Result"; };
			string toString(void){ return "Mock Result"; };
		private:
			shared_ptr<Socket> _socket;
		};
	}
}
#endif
#ifndef _CPP_NET_HTTP_REQUEST_BODY_H_
#define _CPP_NET_HTTP_REQUEST_BODY_H_

#include <stdint.h>
#include <string>
using namespace std;

namespace cpp{
	namespace net{
		class HttpRequestBody{
		public:
			string toString(void){ return "xx"; }

			string contentType(void)
			{
				return _contentType;
			}

			void contentType(string type)
			{
				_contentType = type;
			}

		private:
			string _contentType;
		};
	}
}
#endif
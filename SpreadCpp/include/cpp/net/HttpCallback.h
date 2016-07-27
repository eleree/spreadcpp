#ifndef _CPP_NET_HTTP_CALLBACK_H_
#define _CPP_NET_HTTP_CALLBACK_H_

#include <iostream>
#include <stdint.h>

using namespace std;

namespace cpp{
	namespace net{
		class HttpCallback{
			virtual void onSuccess(void){}
			virtual void onTimeout(void){}
			virtual void onError(int32_t errorCode){}
		};
	}
}
#endif
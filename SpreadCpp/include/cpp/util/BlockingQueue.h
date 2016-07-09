#ifndef _CPP_UTIL_BLOCKING_QUEUE_H_
#define _CPP_UTIL_BLOCKING_QUEUE_H_

#include <iostream>
#include <stdint.h>
#include <cpp/util/Queue.h>

using namespace std;
namespace cpp{
	namespace util{
		template<typename T>
		class BlockingQueue : public Queue<T>{

		};
	}
}
#endif
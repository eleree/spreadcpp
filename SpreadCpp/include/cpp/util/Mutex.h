#ifndef _CPP_UTIL_MUTEX_H_
#define _CPP_UTIL_MUTEX_H_

#if defined(_WIN32) ||  defined(_WIN64)
#include <windows.h>
#endif

namespace cpp{
	namespace util{
		class Mutex{
		public:
			Mutex(){}
			~Mutex(){}
		private:
#if defined(_WIN32) ||  defined(_WIN64)

#endif
		};
	}
}

#endif
#ifndef _CPP_UTIL_LOCK_GUARD_H_
#define _CPP_UTIL_LOCK_GUARD_H_

#include <cpp/util/Mutex.h>

namespace cpp{
	namespace util{
		class LockGuard{
		public:
			LockGuard(Mutex& mutex):_mutex(mutex)
			{
				_mutex.lock();
			}

			~LockGuard()
			{
				_mutex.unlock();
			}
		private:
			Mutex & _mutex;
		};
	}
}

#endif
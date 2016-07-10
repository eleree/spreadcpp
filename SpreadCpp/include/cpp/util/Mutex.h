#ifndef _CPP_UTIL_MUTEX_H_
#define _CPP_UTIL_MUTEX_H_

#if defined(_WIN32) ||  defined(_WIN64)
#include <windows.h>
#endif

namespace cpp{
	namespace util{
		class Mutex{
		public:
			Mutex(){
#if defined(_WIN32) ||  defined(_WIN64)
				_mutex = CreateMutex(
					NULL,              // default security attributes
					FALSE,             // initially not owned
					NULL);             // unnamed mutex
#endif
			}

			void lock()
			{
#if defined(_WIN32) ||  defined(_WIN64)
				::WaitForSingleObject(
					_mutex,    // handle to mutex
					INFINITE);  // no time-out interval
#endif
			}

			void unlock()
			{
#if defined(_WIN32) ||  defined(_WIN64)
				::ReleaseMutex(_mutex);
#endif
			}

			~Mutex()
			{
#if defined(_WIN32) ||  defined(_WIN64)
				::CloseHandle(_mutex);
#endif
			}
		private:

#if defined(_WIN32) ||  defined(_WIN64)
			HANDLE _mutex;
#endif

			Mutex(const Mutex&); // no copyable
			const Mutex& operator=(const Mutex&); 
		};
	}
}

#endif
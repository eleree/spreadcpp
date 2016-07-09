#ifndef _CPP_LANG_THREAD_H_
#define _CPP_LANG_THREAD_H_

using namespace std;

#if defined(_WIN32) ||  defined(_WIN64)
#include <windows.h>
#endif

namespace cpp{
	namespace util{
		class Thread {

		public:
			enum{
				NEW = 0,
				RUNNING,
				BLOCKED,
				STOP,
				TIMED_WAITING,
				TERMINATED
			};

			Thread():_threadStatus(Thread::NEW){}
			virtual ~Thread()
			{
#if defined(_WIN32) ||  defined(_WIN64)
				if ( _thread != NULL )
					CloseHandle(_thread);
#endif
			}

			static void sleep(uint32_t time)
			{
#if defined(_WIN32) ||  defined(_WIN64)
				Sleep(time);
#endif
			}

			void start()
			{
#if defined(_WIN32) ||  defined(_WIN64)
				_thread = CreateThread(
					NULL,                   // default security attributes
					0,                      // use default stack size  
					_threadFunction,       // thread function name
					this,          // argument to thread function 
					0,                      // use default creation flags 
					&_threadId);   // returns the thread identifier 

				if (_thread != NULL)
					Thread::setStatus(Thread::RUNNING);
#endif
			}

			int32_t status(void)
			{
				return _threadStatus;
			}

			void join(uint32_t time)
			{
#if defined(_WIN32) ||  defined(_WIN64)
				if (time == 0)
					WaitForSingleObject(_thread, INFINITE);
				else
					WaitForSingleObject(_thread, time);
#endif
			}

			virtual void run() = 0;

			virtual void stop() = 0;

			void terminate(int32_t exitCode)
			{
#if defined(_WIN32) ||  defined(_WIN64)
				if (_thread != NULL && status() == Thread::RUNNING)
				{
					TerminateThread(_thread, exitCode);
					_thread = NULL;
					Thread::setStatus(Thread::TERMINATED);
				}
#endif
			}

			void setStatus(int32_t status)
			{
				_threadStatus = status;
			}

		private:
			int32_t _threadStatus;

#if defined(_WIN32) ||  defined(_WIN64)
			HANDLE  _thread;
			DWORD _threadId;
			static DWORD WINAPI _threadFunction(LPVOID lpParam)
			{
				Thread * thisThread = (Thread *)(lpParam);
				thisThread->run();		
				thisThread->setStatus(Thread::STOP);
				return 0;
			}
#endif
		};

	}
}

#endif
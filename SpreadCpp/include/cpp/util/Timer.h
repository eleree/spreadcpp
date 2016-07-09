#ifndef _CPP_UTIL_TIMER_H_
#define _CPP_UTIL_TIMER_H_

#include <iostream>
#include <stdint.h>

#include <list>
using namespace std;

namespace cpp{
	namespace util{
		class Timer {
		public:
			class TimerTask
			{
			public:
				TimerTask(){};
				virtual ~TimerTask(){};
				virtual void run() { cout << "Timer Task" << endl; };
			};

			struct TimerTaskInfo{
				TimerTask * task;
				int32_t delay;
				int32_t period;
			};

			void schedule(TimerTask* timerTask, int32_t delay, int32_t period)
			{
				timerTask->run();
			}
		private:
			list<TimerTask *> _taskList;
		};
	}
}
#endif
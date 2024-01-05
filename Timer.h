#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <iostream>
#include<chrono>

namespace sdds
{
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::steady_clock> startTime;

	public:
		void start();
		long long stop();
	};
}

#endif
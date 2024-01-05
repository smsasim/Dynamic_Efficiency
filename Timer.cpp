#include "Timer.h"
#include<iostream>
#include<chrono>

using namespace std;

namespace sdds
{
    void Timer::start() {
        startTime = chrono::steady_clock::now();
    }

    long long Timer::stop() {
        auto end_time = chrono::steady_clock::now();
        auto elapsed_time = chrono::duration_cast<std::chrono::nanoseconds>(end_time - startTime);
        return elapsed_time.count();
    }
}
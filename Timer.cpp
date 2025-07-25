//
// Created by Theo Louvel on 25/07/2025.
//

#include <iostream>
#include "Timer.h"

Timer::Timer(bool start_now)
    : _running(false)
{
    if ( start_now)
    {
        start();
    }
}

void Timer::start()
{
    _running = true;
    _start = Clock::now();
}

void Timer::stop()
{
    if (_running)
    {
        _finish = Clock::now();
        _running = false;
    }
}

double Timer::elapsed() const
{
    return Duration((_running ? Clock::now() : _finish)  - _start).count();
}

std::string Timer::str() const
{
    std::ostringstream oss;
    oss  << elapsed() << "ms";
    return oss.str();
}

void Timer::print() const
{
    std::cout << str() << std::endl;
}
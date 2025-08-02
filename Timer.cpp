//
// Created by Theo Louvel on 25/07/2025.
//

#include <iostream>
#include "Timer.h"

Timer::Timer(bool start_now)
    : running_(false)
{
    if ( start_now)
    {
        start();
    }
}

void Timer::start()
{
    running_ = true;
    start_ = Clock::now();
}

void Timer::stop()
{
    if (running_)
    {
        stop_ = Clock::now();
        running_ = false;
    }
}

void Timer::reset()
{
    // 'this' syntax allows us to bypass variable shadowing
    // 'this' is a pointer to the current instance
    // the arrow syntax A->B allows us to dereference the pointer; it is equivalent to (*A).B
    // However it's best to avoid variable shadowing altogether
    this->running_ = false;
    this->start_ = Clock::now();
    this->stop_ = Clock::now();
}

// We use const to indicate to the compiler this function doesn't modify the instance it is applied to
// If we use const when modifying an instance, the compiler yields an error 'read-only structure'
double Timer::elapsed() const
{
    return Duration((running_ ? Clock::now() : stop_)  - start_).count();
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
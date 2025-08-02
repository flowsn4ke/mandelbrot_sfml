//
// Created by Theo Louvel on 25/07/2025.
//

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<double, std::milli>;

    explicit Timer(bool start_now = true);

    void start();

    void stop();

    void reset();

    [[nodiscard]] double elapsed() const;

    [[nodiscard]] std::string str() const;

    void print() const;

// Everything is private by default.
private:
    // It's common to use an underscore at the end of the variable to avoid variable shadowing (scope) issues
    Clock::time_point start_;
    Clock::time_point stop_;
    bool running_;
};



#endif //TIMER_H

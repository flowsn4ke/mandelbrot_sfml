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

    [[nodiscard]] double elapsed() const;

    [[nodiscard]] std::string str() const;

    void print() const;

private:
    Clock::time_point _start;
    Clock::time_point _finish;
    bool _running;
};



#endif //TIMER_H

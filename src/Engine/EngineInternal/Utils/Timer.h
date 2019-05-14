#pragma once

#include <iostream>
#include <chrono>

class Timer
{
    public:
        Timer() : beg_(clock_::now()) {}
        void reset() { beg_ = clock_::now(); }
        double elapsed() const {
            return std::chrono::duration_cast<milisecond_>(clock_::now() - beg_).count(); }
        double total() const {
            return std::chrono::duration_cast<milisecond_>(clock_::now() - beg_).count(); }

    private:
        typedef std::chrono::high_resolution_clock clock_;
        typedef std::chrono::duration<double, std::ratio<1, 1000>> milisecond_;
        std::chrono::time_point<clock_> beg_;
};
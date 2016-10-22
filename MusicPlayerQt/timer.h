#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <QDebug>


class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void stop();
    void reset();
    unsigned int getSecond();

public:
    void tick();
    bool isStopped = true;
    unsigned int sec = 0;
};

#endif // TIMER_H

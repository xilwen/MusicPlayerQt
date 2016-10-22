#include "timer.h"

Timer::Timer()
{

}

Timer::~Timer()
{
    stop();
}

void Timer::start()
{
    if(isStopped == false)
        return;
    isStopped = false;
    std::thread timerThreadStarter(&Timer::tick, this);
    timerThreadStarter.detach();
}

void Timer::stop()
{
    isStopped = true;
}

void Timer::tick()
{
    while(isStopped == false)
    {
        ++sec;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Timer::reset()
{
    stop();
    sec = 0;
}

unsigned int Timer::getSecond()
{
    return sec;
}

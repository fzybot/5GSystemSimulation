#include "Simulator.h"

Simulator::Simulator()
{
    stop_ = false;
}

void Simulator::run()
{

}

void Simulator::stop()
{
    stop_ = true;
}

void Simulator::setTime(double time)
{
    stopTime_ = time;
}

void Simulator::setCurrentTime(int time)
{
    currentTime_ = time;
}

int Simulator::getCurrentTime()
{
    return currentTime_;
}
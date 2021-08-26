#pragma once


class Simulator
{

private:
    bool stop_;
    int startTime_ = 0;
    int currentTime_;
    int stopTime_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    Simulator();

// ----- [ RUN ] -------------------------------------------------------------------------------------------------------
    void run(void);
    void stop(void);

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

    void setTime(double time);
    void setCurrentTime(int time);
    int getCurrentTime();
};

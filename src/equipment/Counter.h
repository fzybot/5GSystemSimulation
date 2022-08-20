#ifndef COUNTER_H
#define COUNTER_H


class Counter
{
private:
    int _dataTransmitted = 0;


public:
    Counter();

    void countDataTransmitted(int val);

};

#endif // COUNTER_H

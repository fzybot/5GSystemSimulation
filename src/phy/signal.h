#ifndef SIGNAL_H
#define SIGNAL_H

#include<QVector>

class Bandwidth;


class Signal
{
public:
    Signal();
    virtual ~Signal() = default;

    void setPowerValues(QVector< QVector<double> > powerValues);
    QVector< QVector<double> > getPowerValues(void);

    void setIOValues(QVector< QVector<double> > phases);
    QVector< QVector<double> > getIOValues(void);
    void prindIOValues();

    void generateRandomIOValues(int MIMOSize, int dataSize);


private:
    int m_sampleRate;
    QVector< QVector<double> > m_powerValues;
    QVector< QVector<double> > m_IOvalues;

};

#endif // SIGNAL_H

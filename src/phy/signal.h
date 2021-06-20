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

    void setPhases(QVector< QVector<double> > phases);
    QVector< QVector<double> > getPhases(void);

    void generateRandomPhases(int MIMOSize, int dataSize);

private:
    QVector< QVector<double> > m_powerValues;
    QVector< QVector<double> > m_phases;

};

#endif // SIGNAL_H

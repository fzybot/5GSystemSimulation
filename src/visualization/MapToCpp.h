#ifndef MAPTOCPP_H
#define MAPTOCPP_H

#include <QObject>
#include <QDebug>

class MapToCpp : public QObject
{
    Q_OBJECT

public:
    MapToCpp();

public slots:
    void signalsFormQML(const QString &msg);
};

#endif // MAPTOCPP_H

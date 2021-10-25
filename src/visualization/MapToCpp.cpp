#include "MapToCpp.h"

MapToCpp::MapToCpp()
{

}

void MapToCpp::signalsFormQML(const QString &msg)
{
        qDebug()<<"cpp recv msg"<<msg;
}

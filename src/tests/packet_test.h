#pragma once

#include <QDebug>
#include <QVector>

#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/Packet.h"
#include "src/protocols/pdcp_layer/PdcpEntity.h"
#include "src/protocols/phy/ResourceGrid.h"

void pdcp_test(){
    
    RadioBearer *bearer;
    Packet pack(100, 0, 20, bearer);
    PdcpEntity pdcp(&pack);
    qDebug() << "PDCP PDU SIZE --> " << pack.getData();
}

void vectorTest(){
    QVector<QVector<int>> test;

    test.resize(5);
    test[0].resize(2);
    qDebug() << test;
}
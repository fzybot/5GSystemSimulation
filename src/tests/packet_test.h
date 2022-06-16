#pragma once

#include <QDebug>

#include "src/protocols/bearers/RadioBearer.h"
#include "src/protocols/Packet.h"
#include "src/protocols/pdcp_layer/PdcpEntity.h"

void pdcp_test(){

    RadioBearer *bearer;
    Packet pack(100, 0, 20, bearer);
    PdcpEntity pdcp(&pack);
    qDebug() << "PDCP PDU SIZE --> " << pack.getData();
    
}

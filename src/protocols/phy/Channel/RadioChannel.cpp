#include "RadioChannel.h"
#include "src/debug.h"


RadioChannel::RadioChannel()
{
     debug("Radio channel is created: ");
}


void RadioChannel::addDevice(Equipment* e)
{
    debug("RadioChannel: adding an Equipment ");
    // QVector<Equipment*>::iterator it, end_pos;
    // end_pos = connectedDevices_->end();
    // debug(end_pos);
    //connectedDevices_->insert(end_pos, e);

    // TODO: check the existance of the Equipment* e
    //getConnectedDevices()->push_back(e);
    getConnectedDevices()->append(e);
    debug("RadioChannel: equipment is successfully added");
}

QVector<Equipment*>* RadioChannel::getConnectedDevices()
{
    return connectedDevices_;
}
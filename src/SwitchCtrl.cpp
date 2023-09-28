#include "../include/SwitchCtrl.h"

void SwitchCtrl::addNet(RadioInterface *radioInterface, NetComponent *netCmp, uint8_t receiver, uint8_t receiverPort)
{
    NetInterface::addNet(radioInterface, netCmp, receiver, receiverPort);
    this->addHandler(this, 1);
}

void SwitchCtrl::call(uint8_t type, uint8_t idx)
{
    lastType = type;
    sendCommand(CMD_CALL);
    lastType = 0;
    sendCommand(CMD_CALL);
}

void SwitchCtrl::sendValues()
{
    sendCommand(CMD_CALL);
}

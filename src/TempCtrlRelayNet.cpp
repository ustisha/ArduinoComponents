#include "../include/TempCtrlRelayNet.h"

void TempCtrlRelayNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd >= CMD_RELAY) {
        sendPacket(n, r, rp, cmd, tempCtrl->getRelayState());
    }
    TempCtrlNet::sendCommandData(n, r, rp, cmd);
}

void TempCtrlRelayNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelayNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));
    if (p->getCommand() == CMD_RELAY) {
        tempCtrl->setRelayState(p->getData());
    }
    TempCtrlNet::receiveCommandData(p);
}

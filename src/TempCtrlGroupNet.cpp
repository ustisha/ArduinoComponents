#include "../include/TempCtrlGroupNet.h"

void TempCtrlGroupNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd == CMD_MODE) {
        sendPacket(n, r, rp, cmd, tempCtrlGroup->getMode());
    }
}

void TempCtrlGroupNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_MODE) {
        tempCtrlGroup->syncMode(p->getData());
    }
}

#include "../include/SwitchNet.h"

void SwitchNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd == CMD_CALL) {
        sendPacket(n, r, rp, cmd, buttonCtrl->lastType);
    }
}

void SwitchNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[ButtonNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_INFO) {
        if (p->getData() == CMD_GET_VALUES) {
            buttonCtrl->sendValues();
        }
    }
}

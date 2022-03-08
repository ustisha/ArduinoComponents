#include "../include/ValueIntNet.h"

void ValueIntNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) {
    sendPacket(n, r, rp, cmd, valueInt->get());
}

void ValueIntNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[ValueIntNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_VALUE) {
        valueInt->set(p->getData());
        valueInt->render();
    }
}

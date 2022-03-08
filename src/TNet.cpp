#include "../include/TNet.h"

void TNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    sendPacket(n, r, rp, cmd, round(temperature->get() * 100));
}

void TNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_TEMPERATURE) {
        temperature->set((float) p->getData() / 100);
        temperature->setStatus(1);
        temperature->render();
    }
}

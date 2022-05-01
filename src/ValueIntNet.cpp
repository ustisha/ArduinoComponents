#include "../include/ValueIntNet.h"

void ValueIntNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd == CMD_VALUE) {
        sendPacket(n, r, rp, cmd, valueInt->getRaw());
    } else if (cmd == CMD_MAP_MIN) {
        sendPacket(n, r, rp, cmd, valueInt->inputMin);
    } else if (cmd == CMD_MAP_MAX) {
        sendPacket(n, r, rp, cmd, valueInt->inputMax);
    } else {
        sendPacket(n, r, rp, cmd, valueInt->get());
    }
}

void ValueIntNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[ValueIntNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_INFO) {
        if (p->getData() == CMD_GET_VALUES) {
            valueInt->sendValues();
        }
    } else if (p->getCommand() == CMD_VALUE) {
        valueInt->set(p->getData());
        valueInt->render();
    } else if (p->getCommand() == CMD_MAP_MIN) {
        valueInt->setInputMin((int16_t) p->getData());
    } else if (p->getCommand() == CMD_MAP_MAX) {
        valueInt->setInputMax((int16_t) p->getData());
    }
}

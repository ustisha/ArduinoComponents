#include "../include/CtrlRelayNet.h"

void CtrlRelayNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd == CMD_RELAY) {
        sendPacket(n, r, rp, cmd, ctrl->relay->isOn() ? RELAY_ON : RELAY_OFF);
    }
}

void CtrlRelayNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlRelayNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_INFO) {
        if (p->getData() == CMD_GET_VALUES) {
            ctrl->sendValues();
        }
    } else if (p->getCommand() == CMD_RELAY) {
        if (p->getData() == RELAY_ON) {
            ctrl->relay->on();
        } else if (p->getData() == RELAY_OFF) {
            ctrl->relay->off();
        } else if (p->getData() == RELAY_CHANGE) {
            ctrl->relay->change();
        }
    }
}

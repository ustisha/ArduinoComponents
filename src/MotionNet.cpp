#include "../include/MotionNet.h"

void MotionNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd == CMD_MOTION) {
        sendPacket(n, r, rp, cmd, motion->isPressed());
    }
}

void MotionNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[MotionNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_INFO) {
        if (p->getData() == CMD_GET_VALUES) {
            motion->sendValues();
        }
    }
}

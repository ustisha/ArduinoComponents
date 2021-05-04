#include "../include/MotionNet.h"

void MotionNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    sendPacket(n, r, rp, cmd, motion->isPressed());
}

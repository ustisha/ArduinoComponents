#include "../include/THNet.h"

void THNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (tempHum->getStatus() == -1) {
        return;
    }
    if (cmd == CMD_TEMPERATURE) {
        sendPacket(n, r, rp, cmd, (long) (tempHum->get() * 100));
    } else if (cmd == CMD_HUMIDITY) {
        sendPacket(n, r, rp, cmd, (long) tempHum->getHumidity() * 100);
    }
}

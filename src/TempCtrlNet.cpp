#include "../include/TempCtrlNet.h"

void TempCtrlNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd == CMD_MODE) {
        sendPacket(n, r, rp, cmd, tempCtrl->mode);
    } else if (cmd == CMD_DOWN_LIMIT) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->downLimit * 100));
    } else if (cmd == CMD_UP_LIMIT) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->upLimit * 100));
    } else if (cmd == CMD_TIMEOUT) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->timeout));
    }
}

void TempCtrlNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_INFO) {
        if (p->getData() == CMD_GET_VALUES) {
            tempCtrl->sendValues();
        }
    } else if (p->getCommand() == CMD_MODE) {
        tempCtrl->setMode(p->getData());
    } else if (p->getCommand() == CMD_DOWN_LIMIT) {
        tempCtrl->setDownLimit(float(p->getData()) / 100);
    } else if (p->getCommand() == CMD_UP_LIMIT) {
        tempCtrl->setUpLimit(float(p->getData()) / 100);
    } else if (p->getCommand() == CMD_TIMEOUT) {
        tempCtrl->setTimeout(p->getData());
    }
}

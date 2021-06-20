#include "../include/TempCtrlRelayNet.h"

void TempCtrlRelayNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd >= CMD_RELAY_00 && cmd <= CMD_RELAY_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getRelayState(cmd - CMD_RELAY_00));
    } else if (cmd >= CMD_RELAY_ON_00 && cmd <= CMD_RELAY_ON_04) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->getRelayRangeOn(cmd - CMD_RELAY_ON_00) * 100));
    } else if (cmd >= CMD_RELAY_OFF_00 && cmd <= CMD_RELAY_OFF_04) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->getRelayRangeOff(cmd - CMD_RELAY_OFF_00) * 100));
    }
    TempCtrlNet::sendCommandData(n, r, rp, cmd);
}

void TempCtrlRelayNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelayNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));
    if (p->getCommand() >= CMD_RELAY_00 && p->getCommand() <= CMD_RELAY_04) {
        tempCtrl->setRelayState(p->getCommand() - CMD_RELAY_00, p->getData());
    } else if (p->getCommand() >= CMD_RELAY_ON_00 && p->getCommand() <= CMD_RELAY_ON_04) {
        tempCtrl->setRelayRangeOn(p->getCommand() - CMD_RELAY_ON_00, float(p->getData()) / 100);
    } else if (p->getCommand() >= CMD_RELAY_OFF_00 && p->getCommand() <= CMD_RELAY_OFF_04) {
        tempCtrl->setRelayRangeOff(p->getCommand() - CMD_RELAY_OFF_00, float(p->getData()) / 100);
    }
    TempCtrlNet::receiveCommandData(p);
}

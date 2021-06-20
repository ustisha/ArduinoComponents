#include "../include/TempCtrlServoNet.h"

void TempCtrlServoNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd >= CMD_SERVO_00 && cmd <= CMD_SERVO_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getServoState(cmd - CMD_SERVO_00));
    } else if (cmd >= CMD_SERVO_MIN_ANGLE_00 && cmd <= CMD_SERVO_MIN_ANGLE_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getServoMin(cmd - CMD_SERVO_MIN_ANGLE_00));
    } else if (cmd >= CMD_SERVO_MAX_ANGLE_00 && cmd <= CMD_SERVO_MAX_ANGLE_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getServoMax(cmd - CMD_SERVO_MAX_ANGLE_00));
    } else if (cmd >= CMD_SERVO_RATIO_00 && cmd <= CMD_SERVO_RATIO_04) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->getServoRatio(cmd - CMD_SERVO_RATIO_00) * 100));
    }
    TempCtrlNet::sendCommandData(n, r, rp, cmd);
}

void TempCtrlServoNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlServoNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() >= CMD_SERVO_00 && p->getCommand() <= CMD_SERVO_04) {
        tempCtrl->setServoState(p->getCommand() - CMD_SERVO_00, p->getData());
    } else if (p->getCommand() >= CMD_SERVO_MIN_ANGLE_00 && p->getCommand() <= CMD_SERVO_MIN_ANGLE_04) {
        tempCtrl->setServoMin(p->getCommand() - CMD_SERVO_MIN_ANGLE_00, p->getData());
    } else if (p->getCommand() >= CMD_SERVO_MAX_ANGLE_00 && p->getCommand() <= CMD_SERVO_MAX_ANGLE_04) {
        tempCtrl->setServoMax(p->getCommand() - CMD_SERVO_MAX_ANGLE_00, p->getData());
    } else if (p->getCommand() >= CMD_SERVO_RATIO_00 && p->getCommand() <= CMD_SERVO_RATIO_04) {
        tempCtrl->setServoRatio(p->getCommand() - CMD_SERVO_RATIO_00, float(p->getData()) / 100);
    }
    TempCtrlNet::receiveCommandData(p);
}

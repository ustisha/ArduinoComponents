#include "../include/TempControllerNet.h"

void TempControllerNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) {
    if (cmd >= CMD_RELAY_00 && cmd <= CMD_RELAY_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getRelayState(cmd - CMD_RELAY_00));
    } else if (cmd >= CMD_RELAY_ON_00 && cmd <= CMD_RELAY_ON_04) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->getRelayRangeOn(cmd - CMD_RELAY_ON_00) *  100));
    } else if (cmd >= CMD_RELAY_OFF_00 && cmd <= CMD_RELAY_OFF_04) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->getRelayRangeOff(cmd - CMD_RELAY_OFF_00) *  100));
    } else if (cmd >= CMD_SERVO_00 && cmd <= CMD_SERVO_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getServoState(cmd - CMD_SERVO_00));
    } else if (cmd >= CMD_SERVO_MIN_ANGLE_00 && cmd <= CMD_SERVO_MIN_ANGLE_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getServoMin(cmd - CMD_SERVO_MIN_ANGLE_00));
    } else if (cmd >= CMD_SERVO_MAX_ANGLE_00 && cmd <= CMD_SERVO_MAX_ANGLE_04) {
        sendPacket(n, r, rp, cmd, tempCtrl->getServoMax(cmd - CMD_SERVO_MAX_ANGLE_00));
    } else if (cmd >= CMD_SERVO_RATIO_00 && cmd <= CMD_SERVO_RATIO_04) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->getServoRatio(cmd - CMD_SERVO_RATIO_00) * 100));
    } else if (cmd == CMD_MODE) {
        sendPacket(n, r, rp, cmd, tempCtrl->mode);
    } else if (cmd == CMD_DOWN_LIMIT) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->downLimit * 100));
    } else if (cmd == CMD_UP_LIMIT) {
        sendPacket(n, r, rp, cmd, lround(tempCtrl->upLimit * 100));
    } else if (cmd == CMD_TIMEOUT) {
        sendPacket(n, r, rp, cmd, tempCtrl->timeout);
    }
}

void TempControllerNet::receiveCommandData(Packet *p) {
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempControllerNet::receiveCommandData] Cmd: %i, Data: %ld\n"), p->getCommand(), p->getData()));

    if (p->getCommand() == CMD_INFO) {
        if (p->getData() == CMD_GET_VALUES) {
            tempCtrl->sendValues();
        }
    } else if (p->getCommand() >= CMD_RELAY_00 && p->getCommand() <= CMD_RELAY_04) {
        tempCtrl->setRelayState(p->getCommand() - CMD_RELAY_00, p->getData());
    } else if (p->getCommand() >= CMD_RELAY_ON_00 && p->getCommand() <= CMD_RELAY_ON_04) {
        tempCtrl->setRelayRangeOn(p->getCommand() - CMD_RELAY_ON_00, float(p->getData()) / 100);
    } else if (p->getCommand() >= CMD_RELAY_OFF_00 && p->getCommand() <= CMD_RELAY_OFF_04) {
        tempCtrl->setRelayRangeOff(p->getCommand() - CMD_RELAY_OFF_00, float(p->getData()) / 100);
    } else if (p->getCommand() >= CMD_SERVO_00 && p->getCommand() <= CMD_SERVO_04) {
        tempCtrl->setServoState(p->getCommand() - CMD_SERVO_00, p->getData());
    } else if (p->getCommand() >= CMD_SERVO_MIN_ANGLE_00 && p->getCommand() <= CMD_SERVO_MIN_ANGLE_04) {
        tempCtrl->setServoMin(p->getCommand() - CMD_SERVO_MIN_ANGLE_00, p->getData());
    } else if (p->getCommand() >= CMD_SERVO_MAX_ANGLE_00 && p->getCommand() <= CMD_SERVO_MAX_ANGLE_04) {
        tempCtrl->setServoMax(p->getCommand() - CMD_SERVO_MAX_ANGLE_00, p->getData());
    } else if (p->getCommand() >= CMD_SERVO_RATIO_00 && p->getCommand() <= CMD_SERVO_RATIO_04) {
        tempCtrl->setServoRatio(p->getCommand() - CMD_SERVO_RATIO_00, float(p->getData()) / 100);
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

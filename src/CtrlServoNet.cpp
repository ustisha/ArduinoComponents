#include "../include/CtrlServoNet.h"

void CtrlServoNet::sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd)
{
    if (cmd == CMD_SERVO_ANGLE) {
        sendPacket(n, r, rp, cmd, ctrl->servo->getCurrentAngle());
    } else if (cmd == CMD_SERVO_PERCENT) {
        sendPacket(n, r, rp, cmd, ctrl->getPercent());
    } else if (cmd == CMD_SERVO_MIN_ANGLE) {
        sendPacket(n, r, rp, cmd, ctrl->minA);
    } else if (cmd == CMD_SERVO_MAX_ANGLE) {
        sendPacket(n, r, rp, cmd, ctrl->maxA);
    } else if (cmd == CMD_SERVO_SPEED) {
        sendPacket(n, r, rp, cmd, ctrl->servoSpeed);
    } else if (cmd == CMD_SERVO_MOVE_TYPE) {
        sendPacket(n, r, rp, cmd, ctrl->servoMoveType);
    }
}

void CtrlServoNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlServoNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_INFO) {
        if (p->getData() == CMD_GET_VALUES) {
            ctrl->sendValues();
        }
    } else if (p->getCommand() == CMD_SERVO_ANGLE) {
        ctrl->servo->easeTo((int16_t) p->getData());
    } else if (p->getCommand() == CMD_SERVO_PERCENT) {
        ctrl->setPercent((int16_t) p->getData());
    } else if (p->getCommand() == CMD_SERVO_MIN_ANGLE) {
        ctrl->setMinA((int16_t) p->getData());
    } else if (p->getCommand() == CMD_SERVO_MAX_ANGLE) {
        ctrl->setMaxA((int16_t) p->getData());
    } else if (p->getCommand() == CMD_SERVO_SPEED) {
        ctrl->setSpeed((uint16_t) p->getData());
    } else if (p->getCommand() == CMD_SERVO_MOVE_TYPE) {
        ctrl->setMoveType((uint8_t) p->getData());
    }
}

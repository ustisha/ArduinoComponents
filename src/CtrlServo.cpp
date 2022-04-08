#include "../include/CtrlServo.h"

CtrlServo::CtrlServo(uint8_t servoPin, int16_t minAngle, int16_t maxAngle) :
        currentA(0),
        minA(minAngle),
        maxA(maxAngle),
        servoSpeed(60),
        servoMoveType(EASE_CUBIC_IN_OUT),
        init(0)
{
    servo = new ServoEasing();
    status = servo->attach(servoPin);

    init.restore();
    if (init != 1) {
        currentA.save();
        minA.save();
        maxA.save();
        servoSpeed.save();
        servoMoveType.save();
        init = 1;
        init.save();
    } else {
        currentA.restore();
        minA.restore();
        maxA.restore();
        servoSpeed.restore();
        servoMoveType.restore();
    }
    minAA = min(minA, maxA);
    maxAA = max(minA, maxA);

    int16_t const moveTo = currentA < minAA ? minAA : (currentA > maxAA ? maxAA : int16_t(currentA));
    servo->setSpeed(servoSpeed);
    servo->setEasingType(servoMoveType);
    IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlServo] MinA: %d, MaxA: %d, MinAA: %d, MaxAA: %d, Speed: %u\n"),
                             (int16_t) minA,
                             (int16_t) maxA,
                             (int16_t) minAA,
                             (int16_t) maxAA,
                             (uint16_t) servoSpeed));

    IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlServo] Restore angle: %d\n"), moveTo));
    servo->startEaseTo(moveTo);
}

uint8_t CtrlServo::getPercent()
{
    return abs(getReverse() + floor(100 / double(maxAA - minAA) * (servo->getCurrentAngle() - minAA)));
}

void CtrlServo::setPercent(uint8_t percent)
{
    servoWrite(floor(double(maxAA - minAA) / 100 * abs(percent + getReverse())) + minAA);
}

void CtrlServo::servoWrite(int16_t angle)
{
    currentA = angle < minAA ? minAA : (angle > maxAA ? maxAA : angle);
    int16_t prevAngle = servo->getCurrentAngle();
    IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlServo::servoWrite] Servo angle: %d, Prev: %d\n"),
                             (uint16_t) currentA,
                             prevAngle));
    servo->startEaseTo(currentA);
    if (currentA != prevAngle) {
        currentA.save();
        sendCommand(CMD_SERVO_ANGLE);
        sendCommand(CMD_SERVO_PERCENT);
    }
}

void CtrlServo::sendValues()
{
    sendCommand(CMD_SERVO_ANGLE);
    sendCommand(CMD_SERVO_PERCENT);
    sendCommand(CMD_SERVO_MAX_ANGLE);
    sendCommand(CMD_SERVO_MIN_ANGLE);
    sendCommand(CMD_SERVO_SPEED);
    sendCommand(CMD_SERVO_MOVE_TYPE);
}

void CtrlServo::tick()
{
    if (servo->isMoving()) {
        sendCommand(CMD_SERVO_ANGLE);
        sendCommand(CMD_SERVO_PERCENT);
    }
}

#include "../include/TempCtrlServo.h"

TempCtrlServo::TempCtrlServo(THInterface *tiface, uint8_t sMax, float down, float up) : TempCtrl(tiface, down, up),
                                                                                        tiface(tiface),
                                                                                        servoControl(new ServoControl[sMax]{}),
                                                                                        servoMax(sMax)
{

}

#ifdef SERVO_EASING
void TempCtrlServo::addServo(ServoEasing *s, uint8_t i, uint8_t type, int minAngle, int maxAngle, float ratio)
#else

void TempCtrlServo::addServo(Servo *s, uint8_t i, uint8_t type, int minAngle, int maxAngle, float ratio)
#endif
{
    if (i >= servoMax) {
        return;
    }
    servoControl[i].enabled = true;
    servoControl[i].servo = s;
    servoControl[i].type = type;
    servoControl[i].minAngle = minAngle;
    servoControl[i].maxAngle = maxAngle;
    servoControl[i].ratio = ratio;
    servoControl[i].servo->write(minAngle);

    if (init != 1) {
        servoControl[i].enabled.save();
        servoControl[i].minAngle.save();
        servoControl[i].maxAngle.save();
        servoControl[i].ratio.save();
    } else {
        servoControl[i].enabled.restore();
        servoControl[i].minAngle.restore();
        servoControl[i].maxAngle.restore();
        servoControl[i].ratio.restore();
    }

#ifdef SERIAL_DEBUG
    char ratioBuf[5] = {};
    Format::floatVar(ratioBuf, ratio);

    IF_SERIAL_DEBUG(
            printf_P(PSTR(
                    "[TempCtrlServo::addServo] Idx: %i, Mode: %d, Min angle: %d, Max angle: %d, Ratio: %s\n"),
                     i, (int) type, (int) servoControl[i].minAngle, (int) servoControl[i].maxAngle, ratioBuf));
#endif
}

void TempCtrlServo::addServoButton(uint8_t i, Button *btn)
{
    btn->addHandler(this, HANDLER_SERVO_AUTO, Button::PRESSTIME_DEFAULT, i);
    btn->addHandler(this, HANDLER_SERVO_OPEN, Button::PRESSTIME_2SEC, i);
    btn->addHandler(this, HANDLER_SERVO_CLOSED, Button::PRESSTIME_4SEC, i);
    servoControl[i].button = btn;
}

void TempCtrlServo::call(uint8_t type, uint8_t idx)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlServo::call] Type: %u, Index: %u \n"), type, idx));
    if (type == HANDLER_SERVO_AUTO) {
        setMode(MODE_AUTO);
    } else if (type == HANDLER_SERVO_OPEN) {
        setServoState(idx, servoControl[idx].maxAngle);
    } else if (type == HANDLER_SERVO_CLOSED) {
        setServoState(idx, servoControl[idx].minAngle);
    }
}

void TempCtrlServo::tick(uint16_t sleep)
{
    for (int i = 0; i < servoMax; ++i) {
        if (servoControl[i].enabled && servoControl[i].button != nullptr) {
            servoControl[i].button->tick();
        }
        if (servoControl[i].enabled) {
#ifdef SERVO_EASING
            if (servoControl[i].servo->isMoving() && (millis() % 50) == 0) {
                sendCommand(CMD_SERVO_00 + i);
            }
#endif
        }
    }
    TempCtrl::tick(sleep);
}

void TempCtrlServo::control()
{
    float value = 0;
    for (int i = 0; i < servoMax; ++i) {
        if (servoControl[i].enabled) {

            if (servoControl[i].type & TYPE_TEMPERATURE) {
                value = tiface->get();
            } else if (servoControl[i].type & TYPE_HUMIDITY) {
                value = tiface->getHumidity();
            }

            int angle = 0;
            int diff;
            if ((servoControl[i].type & TYPE_BELOW_DOWN_LIMIT && value < downLimit) ||
                (servoControl[i].type & TYPE_ABOVE_DOWN_LIMIT && value > downLimit)) {
                diff = abs(value - downLimit);
                angle = round(diff * diff * servoControl[i].ratio);
            }
            if ((servoControl[i].type & TYPE_ABOVE_UP_LIMIT && value > upLimit) ||
                (servoControl[i].type & TYPE_BELOW_UP_LIMIT && value < upLimit)) {
                diff = abs(value - upLimit);
                angle = round(diff * diff * servoControl[i].ratio);
            }
            servoWrite(i, angle);
        }
    }
}

void TempCtrlServo::servoWrite(uint8_t i, int angle)
{
    if (!servoControl[i].enabled) {
        return;
    }
    if (angle < servoControl[i].minAngle) {
        angle = servoControl[i].minAngle;
    }
    if (angle > servoControl[i].maxAngle) {
        angle = servoControl[i].maxAngle;
    }
    int prevAngle = servoControl[i].servo->read();
#ifdef SERVO_EASING
    servoControl[i].servo->startEaseTo(angle);
#else
    servoControl[i].servo->write(angle);
#endif
    if (angle != prevAngle) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlServo::servoWrite] Servo index: %d Angle: %d\n"), i, angle));
        sendCommand(CMD_SERVO_00 + i);
    }
}

auto TempCtrlServo::getServoState(uint8_t i) -> int
{
    if (i >= servoMax) {
        return -1;
    }
    if (!servoControl[i].enabled) {
        return SERVO_DISABLED;
    }
    return servoControl[i].servo->read();
}

void TempCtrlServo::setServoState(uint8_t i, int angle)
{
    if (i >= servoMax) {
        return;
    }
    if (angle == -1) {
        servoControl[i].enabled = false;
        servoControl[i].enabled.update();
    } else {
        servoControl[i].enabled = true;
        servoControl[i].enabled.update();
        setMode(MODE_MANUAL);
        servoWrite(i, angle);
    }
}

auto TempCtrlServo::getServoMin(uint8_t i) -> int
{
    if (getServoState(i) < 0) {
        return getServoState(i);
    }
    return servoControl[i].minAngle;
}

auto TempCtrlServo::getServoMax(uint8_t i) -> int
{
    if (getServoState(i) < 0) {
        return getServoState(i);
    }
    return servoControl[i].maxAngle;
}

auto TempCtrlServo::getServoRatio(uint8_t i) -> float
{
    if (getServoState(i) < 0) {
        return (float) getServoState(i);
    }
    return servoControl[i].ratio;
}

void TempCtrlServo::setServoMin(uint8_t i, int value)
{
    if (i >= servoMax) {
        return;
    }
    servoControl[i].minAngle = value;
    servoControl[i].minAngle.update();
    sendCommand(CMD_SERVO_MIN_ANGLE_00 + i);
    control();
}

void TempCtrlServo::setServoMax(uint8_t i, int value)
{
    if (i >= servoMax) {
        return;
    }
    servoControl[i].maxAngle = value;
    servoControl[i].maxAngle.update();
    sendCommand(CMD_SERVO_MAX_ANGLE_00 + i);
    control();
}

void TempCtrlServo::setServoRatio(uint8_t i, float value)
{
    if (i >= servoMax) {
        return;
    }
    servoControl[i].ratio = value;
    servoControl[i].ratio.update();
    sendCommand(CMD_SERVO_RATIO_00 + i);
    control();
}

void TempCtrlServo::sendValues()
{
    TempCtrl::sendValues();
    for (int i = 0; i < servoMax; ++i) {
        if (servoControl[i].servo != nullptr) {
            sendCommand(CMD_SERVO_00 + i);
            sendCommand(CMD_SERVO_MIN_ANGLE_00 + i);
            sendCommand(CMD_SERVO_MAX_ANGLE_00 + i);
            sendCommand(CMD_SERVO_RATIO_00 + i);
        }
    }
}

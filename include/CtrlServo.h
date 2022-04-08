#ifndef CTRLSERVO_H
#define CTRLSERVO_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Relay.h>
#include <NetInterface.h>
#include <Button.h>
#include <ServoEasing.h>
#include <Format.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

class CtrlServo : public NetInterface, virtual public HandlerInterface
{
public:
    ServoEasing *servo;
    EEPROMVar<int16_t> currentA;
    EEPROMVar<int16_t> minA;
    EEPROMVar<int16_t> maxA;
    EEPROMVar<uint16_t> servoSpeed;
    EEPROMVar<uint8_t> servoMoveType;

    CtrlServo(uint8_t servoPin, int16_t minAngle, int16_t maxAngle);

    void call(uint8_t type, uint8_t idx) override
    {};

    void setMinA(int16_t minAngle)
    {
        minA = minAngle;
        minA.save();
        sendCommand(CMD_SERVO_MIN_ANGLE);
    }

    void setMaxA(int16_t maxAngle)
    {
        maxA = maxAngle;
        maxA.save();
        sendCommand(CMD_SERVO_MAX_ANGLE);
    }

    void setSpeed(uint16_t speed)
    {
        servo->setSpeed(speed);
        servoSpeed = speed;
        servoSpeed.save();
        sendCommand(CMD_SERVO_SPEED);
    }

    void setMoveType(uint8_t type) {
        servo->setEasingType(type);
        servoMoveType = type;
        servoMoveType.save();
        sendCommand(CMD_SERVO_MOVE_TYPE);
    }

    int8_t getReverse()
    {
        return minA > maxA ? -100 : 0;
    }

    void setPercent(uint8_t percent);

    uint8_t getPercent();

    uint8_t getStatus() const
    {
        return status;
    }

    void sendValues();

    void tick();

protected:
    EEPROMVar<uint8_t> init;
    uint8_t status = 0;
    int16_t minAA, maxAA;

    void servoWrite(int16_t angle);
};

#endif //CTRLSERVO_H

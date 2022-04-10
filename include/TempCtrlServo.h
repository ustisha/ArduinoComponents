#ifndef TEMPCTRLSERVO_H
#define TEMPCTRLSERVO_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Config.h>
#include <THInterface.h>
#include <TempCtrl.h>
#include <NetComponent.h>
#include <Relay.h>
#include <Button.h>

#ifdef SERVO_EASING
#include <ServoEasing.h>
#else

#include <Servo.h>

#endif

#include <Format.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

class TempCtrlServo : public TempCtrl, virtual public HandlerInterface
{
    struct ServoControl
    {
        EEPROMVar<bool> enabled = false;
#ifdef SERVO_EASING
        ServoEasing *servo = nullptr;
#else
        Servo *servo = nullptr;
#endif
        uint8_t type = 0;
        EEPROMVar<int> minAngle = 0;
        EEPROMVar<int> maxAngle = 0;
        EEPROMVar<float> ratio = 0;
        Button *button = nullptr;
    };
public:
    const static uint8_t HANDLER_SERVO_AUTO = 1;
    const static uint8_t HANDLER_SERVO_OPEN = 2;
    const static uint8_t HANDLER_SERVO_CLOSED = 3;

    TempCtrlServo(THInterface *tiface, uint8_t sMax, float down, float up);

#ifdef SERVO_EASING
    void addServo(ServoEasing *s, uint8_t i, uint8_t type, int minAngle = 0, int maxAngle = 90, float ratio = 0.8);
#else

    void addServo(Servo *s, uint8_t i, uint8_t type, int minAngle = 0, int maxAngle = 90, float ratio = 0.8);

#endif

    void addServoButton(uint8_t i, Button *btn);

    auto getServoState(uint8_t i) -> int;

    void setServoState(uint8_t i, int angle);

    auto getServoMin(uint8_t i) -> int;

    auto getServoMax(uint8_t i) -> int;

    auto getServoRatio(uint8_t i) -> float;

    void setServoMin(uint8_t i, int value);

    void setServoMax(uint8_t i, int value);

    void setServoRatio(uint8_t i, float value);

    void call(uint8_t type, uint8_t idx) override;

    void tick(uint16_t sleep) override;

    void sendValues() override;

protected:

    void control() override;

    void servoWrite(uint8_t i, int angle);

    ServoControl *servoControl;
    uint8_t servoMax;
};


#endif //TEMPCTRLSERVO_H

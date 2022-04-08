#ifndef CTRLSERVONET_H
#define CTRLSERVONET_H

#include <Arduino.h>
#include <DebugLog.h>
#include <NetComponent.h>
#include <CtrlServo.h>

class CtrlServoNet : public NetComponent
{

public:
    CtrlServoNet(SmartNet *n, uint8_t sp, uint8_t max, CtrlServo *ctrlServo) : NetComponent(n, sp, max)
    {
        ctrl = ctrlServo;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

    void receiveCommandData(Packet *p) override;

protected:
    CtrlServo *ctrl;
};

#endif //CTRLSERVONET_H

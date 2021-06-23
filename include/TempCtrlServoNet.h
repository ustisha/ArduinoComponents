#ifndef TEMPCTRLSERVONET_H
#define TEMPCTRLSERVONET_H

#include <Arduino.h>
#include <DebugLog.h>
#include <NetComponent.h>
#include <TempCtrlServo.h>
#include <TempCtrlNet.h>

class TempCtrlServoNet : public TempCtrlNet
{

public:
    TempCtrlServoNet(SmartNet *n, uint8_t sp, uint8_t max, TempCtrlServo *ctrl) : TempCtrlNet(n, sp, max, ctrl)
    {
        tempCtrl = ctrl;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

    void receiveCommandData(Packet *p) override;

protected:
    TempCtrlServo *tempCtrl;
};

#endif //TEMPCTRLSERVONET_H

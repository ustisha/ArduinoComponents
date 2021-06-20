#ifndef TEMPCTRLNET_H
#define TEMPCTRLNET_H

#include <Arduino.h>
#include <DebugLog.h>
#include <NetComponent.h>
#include <TempCtrl.h>

class TempCtrlNet : public NetComponent
{

public:
    TempCtrlNet(SmartNet *n, uint8_t sp, uint8_t max, TempCtrl *ctrl) : NetComponent(n, sp, max)
    {
        tempCtrl = ctrl;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

    void receiveCommandData(Packet *p) override;

protected:
    TempCtrl *tempCtrl;
};

#endif //TEMPCTRLNET_H

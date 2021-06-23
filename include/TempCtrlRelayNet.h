#ifndef TEMPCTRLRELAYNET_H
#define TEMPCTRLRELAYNET_H

#include <Arduino.h>
#include <DebugLog.h>
#include <TempCtrlRelay.h>
#include <TempCtrlNet.h>

class TempCtrlRelayNet : public TempCtrlNet
{

public:
    TempCtrlRelayNet(SmartNet *n, uint8_t sp, uint8_t max, TempCtrlRelay *ctrl) : TempCtrlNet(n, sp, max, ctrl)
    {
        tempCtrl = ctrl;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

    void receiveCommandData(Packet *p) override;

protected:
    TempCtrlRelay *tempCtrl;
};

#endif //TEMPCTRLRELAYNET_H

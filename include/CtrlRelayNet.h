#ifndef CTRLRELAYNET_H
#define CTRLRELAYNET_H

#include <Arduino.h>
#include <DebugLog.h>
#include <NetComponent.h>
#include <CtrlRelay.h>

class CtrlRelayNet : public NetComponent
{

public:
    CtrlRelayNet(SmartNet *n, uint8_t sp, uint8_t max, CtrlRelay *ctrlRelay) : NetComponent(n, sp, max)
    {
        ctrl = ctrlRelay;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

    void receiveCommandData(Packet *p) override;

protected:
    CtrlRelay *ctrl;
};

#endif //CTRLRELAYNET_H

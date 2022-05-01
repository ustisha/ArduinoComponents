#ifndef TEMPCTRLGROUPNET_H
#define TEMPCTRLGROUPNET_H

#include <Arduino.h>
#include <DebugLog.h>
#include <Config.h>
#include <TempCtrlGroup.h>

class TempCtrlGroupNet : public NetComponent
{

public:
    TempCtrlGroupNet(SmartNet *n, uint8_t sp, uint8_t max, TempCtrlGroup *ctrlGroup) : NetComponent(n, sp, max)
    {
        tempCtrlGroup = ctrlGroup;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

    void receiveCommandData(Packet *p) override;

protected:
    TempCtrlGroup *tempCtrlGroup;
};

#endif //TEMPCTRLGROUP_H

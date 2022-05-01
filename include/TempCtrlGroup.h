#ifndef TEMPCTRLGROUP_H
#define TEMPCTRLGROUP_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Config.h>
#include <TempCtrl.h>
#include <NetInterface.h>

class TempCtrlGroup : public NetInterface, GroupHandlerInterface
{
public:

    explicit TempCtrlGroup(uint8_t tempMax);

    void addTempCtrl(TempCtrl *tempCtrl, uint8_t idx);

    uint8_t getMode() const
    {
        return groupMode;
    }

    void sendValues();

    void call(uint8_t type, uint8_t idx) override;

    void syncMode(uint8_t mode) override;

    void syncMode()override;

protected:
    struct TempControls
    {
        TempCtrl *ctrl = nullptr;
    };

    TempControls *tempControls;
    uint8_t tMax, groupMode;
};

#endif //TEMPCTRLGROUP_H

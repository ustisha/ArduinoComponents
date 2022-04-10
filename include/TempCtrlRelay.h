#ifndef TEMPCTRLRELAY_H
#define TEMPCTRLRELAY_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <TempCtrl.h>
#include <THInterface.h>
#include <NetInterface.h>
#include <NetComponent.h>
#include <CtrlRelay.h>
#include <Format.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

class TempCtrlRelay : public TempCtrl, virtual public HandlerInterface
{
public:

    CtrlRelay *ctrlRelay;

    TempCtrlRelay(THInterface *tiface, CtrlRelay *ctrlRelay, float down, float up, uint8_t s);

    auto getRelayState() const -> int
    {
        return ctrlRelay->relay->isOn() ? RELAY_ON : RELAY_OFF;
    }

    void setRelayState(uint8_t state)
    {
        if (state == RELAY_ON) {
            setMode(MODE_MANUAL);
            ctrlRelay->call(RELAY_ON, 0);
        } else if (state == RELAY_OFF) {
            setMode(MODE_MANUAL);
            ctrlRelay->call(RELAY_OFF, 0);
        }
        sendCommand(CMD_RELAY);
    }

    void setMode(uint8_t m) override;

    void call(uint8_t type, uint8_t idx) override;

    void sendValues() override;

protected:

    void control() override;

    uint8_t settings = 0;
};


#endif //TEMPCTRLRELAY_H

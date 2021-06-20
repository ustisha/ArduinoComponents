#ifndef TEMPCTRLRELAY_H
#define TEMPCTRLRELAY_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <TempCtrl.h>
#include <THInterface.h>
#include <NetInterface.h>
#include <NetComponent.h>
#include <RelayInterface.h>
#include <Button.h>
#include <Format.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

class TempCtrlRelay : public TempCtrl, virtual public HandlerInterface
{
    struct RelayControl
    {
        EEPROMVar<bool> enabled = false;
        RelayInterface *relay = nullptr;
        uint8_t type = 0;
        EEPROMVar<float> rangeOn = 0;
        EEPROMVar<float> rangeOff = 0;
    };
public:

    TempCtrlRelay(THInterface *tiface, uint8_t rMax, float down, float up);

    void addRelay(RelayInterface *r, uint8_t i, uint8_t type, float rangeOn = 0.1, float rangeOff = 0.0);

    auto getRelayState(uint8_t i) -> int;

    void setRelayState(uint8_t i, uint8_t state);

    auto getRelayRangeOn(uint8_t i) -> float;

    auto getRelayRangeOff(uint8_t i) -> float;

    void setRelayRangeOn(uint8_t i, float value);

    void setRelayRangeOff(uint8_t i, float value);

    void sendValues() override;

    void call(uint8_t type, uint8_t idx) override
    {};

protected:

    void relayOn(uint8_t i);

    void relayOff(uint8_t i);

    void control() override;

    THInterface *tiface;
    RelayControl *relayControl;
    uint8_t relayMax;
};


#endif //TEMPCTRLRELAY_H

#ifndef CTRLRELAY_H
#define CTRLRELAY_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Config.h>
#include <Button.h>
#include <Relay.h>
#include <NetInterface.h>
#include <Format.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

class CtrlRelay : public NetInterface, virtual public HandlerInterface
{
public:
    const static uint8_t MODE_ONE_BUTTON = B00000001;
    const static uint8_t MODE_ON = B00000010;
    const static uint8_t MODE_OFF = B00000100;

    RelayInterface *relay;
    EEPROMVar<uint8_t> state;

    explicit CtrlRelay(RelayInterface *r);

    void addButton(Button *btn, uint8_t mode = MODE_ONE_BUTTON, uint8_t defaultAct = RELAY_ON);

    void call(uint8_t type, uint8_t idx) override;

    void sendValues();

    void tick();

protected:
    EEPROMVar<uint8_t> init;
    Button *buttons[2] = {nullptr, nullptr};
};

#endif //CTRLRELAY_H

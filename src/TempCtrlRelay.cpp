#include "../include/TempCtrlRelay.h"

TempCtrlRelay::TempCtrlRelay(THInterface *tiface, CtrlRelay *ctrlRelay, float down, float up, uint8_t s)
        : TempCtrl(tiface, down, up), ctrlRelay(ctrlRelay), settings(s)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelay] Settings: %i\n"), settings));
}

void TempCtrlRelay::call(uint8_t type, uint8_t idx)
{
    ctrlRelay->call(type, idx);
    sendCommand(CMD_RELAY);
    if (groupHandler != nullptr) {
        groupHandler->call(type, idx);
    }
}

void TempCtrlRelay::setMode(uint8_t m)
{
    if (m == MODE_MANUAL) {
        call(RELAY_OFF, groupIdx);
    }
    TempCtrl::setMode(m);
}

void TempCtrlRelay::control()
{
    float value = 0;
    if (tiface->getStatus() <= 0) {
        return;
    }
    if (settings & TYPE_TEMPERATURE) {
        value = tiface->get();
    } else if (settings & TYPE_HUMIDITY) {
        value = tiface->getHumidity();
    }

#ifdef SERIAL_DEBUG
    char valueBuf[8]{};
    Format::floatVar(valueBuf, value);
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelay::control] Current value: %s\n"), valueBuf));
#endif

    if (settings & TYPE_BELOW_DOWN_LIMIT) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelay::control] BELOW_DOWN ABOVE_UP \n")));
        if (value < downLimit) {
            call(RELAY_ON, groupIdx);
        } else if (value > upLimit) {
            call(RELAY_OFF, groupIdx);
        }
    } else if (settings & TYPE_ABOVE_UP_LIMIT) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelay::control] ABOVE_UP BELOW_DOWN \n")));
        if (value > upLimit) {
            call(RELAY_ON, groupIdx);
        } else if (value < downLimit) {
            call(RELAY_OFF, groupIdx);
        }
    }
}

void TempCtrlRelay::sendValues()
{
    TempCtrl::sendValues();
    sendCommand(CMD_RELAY);
}

#include "../include/TempCtrlRelay.h"

TempCtrlRelay::TempCtrlRelay(THInterface *tiface, uint8_t rMax, float down, float up) : TempCtrl(tiface, down, up),
                                                                                        tiface(tiface),
                                                                                        relayControl(new RelayControl[rMax]{}),
                                                                                        relayMax(rMax)
{

}

void TempCtrlRelay::addRelay(RelayInterface *r, uint8_t i, uint8_t type, float rangeOn, float rangeOff)
{
    if (i >= relayMax) {
        return;
    }
    relayControl[i].enabled = true;
    relayControl[i].relay = r;
    relayControl[i].type = type;
    relayControl[i].rangeOn = rangeOn;
    relayControl[i].rangeOff = rangeOff;

    if (init != 1) {
        relayControl[i].enabled.save();
        relayControl[i].rangeOn.save();
        relayControl[i].rangeOff.save();
    } else {
        relayControl[i].enabled.restore();
        relayControl[i].rangeOn.restore();
        relayControl[i].rangeOff.restore();
    }

#ifdef SERIAL_DEBUG
    char onBuf[8] = {};
    char offBuf[8] = {};
    Format::floatVar(onBuf, relayControl[i].rangeOn);
    Format::floatVar(offBuf, relayControl[i].rangeOff);

    IF_SERIAL_DEBUG(
            printf_P(PSTR("[TempCtrlRelay::addRelay] Idx: %i, Mode: %d, On: %s, Off: %s\n"),
                     i, (int) type, onBuf, offBuf));
#endif
}

void TempCtrlRelay::control()
{
    float value = 0;
    for (int i = 0; i < relayMax; ++i) {
        if (relayControl[i].enabled) {
            if (tiface->getStatus() <= 0) {
                break;
            }
            if (relayControl[i].type & TYPE_TEMPERATURE) {
                value = tiface->get();
            } else if (relayControl[i].type & TYPE_HUMIDITY) {
                value = tiface->getHumidity();
            }

            float downLimitOn = (downLimit - relayControl[i].rangeOn);
            float downLimitOff = (downLimitOn + relayControl[i].rangeOff);
            float upLimitOn = (upLimit - relayControl[i].rangeOn);
            float upLimitOff = (upLimitOn + relayControl[i].rangeOff);
            if (relayControl[i].type & TYPE_BELOW_DOWN_LIMIT) {
                if (value < downLimitOn) {
                    relayOn(i);
                } else {
                    if (relayControl[i].type & TYPE_BELOW_UP_LIMIT) {
                        if (value > upLimitOff) {
                            relayOff(i);
                        }
                    } else if (relayControl[i].type & TYPE_ABOVE_DOWN_LIMIT) {
                        if (value > downLimitOff) {
                            relayOff(i);
                        }
                    }
                }
            } else if (relayControl[i].type & TYPE_ABOVE_UP_LIMIT) {
                if (value > upLimitOn) {
                    relayOn(i);
                } else {
                    if (relayControl[i].type & TYPE_ABOVE_DOWN_LIMIT) {
                        if (value < downLimitOff) {
                            relayOff(i);
                        }
                    } else if (relayControl[i].type & TYPE_BELOW_UP_LIMIT) {
                        if (value < upLimitOff) {
                            relayOff(i);
                        }
                    }
                }
            }
        }
    }
}

void TempCtrlRelay::relayOff(uint8_t i)
{
    if (!relayControl[i].enabled || !relayControl[i].relay->isOn()) {
        return;
    }
    relayControl[i].relay->off();
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelay::relayOff] Relay index: %d OFF\n"), i));
    sendCommand(CMD_RELAY_00 + i);
}

void TempCtrlRelay::relayOn(uint8_t i)
{
    if (!relayControl[i].enabled || relayControl[i].relay->isOn()) {
        return;
    }
    relayControl[i].relay->on();
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlRelay::relayOn] Relay index: %d ON\n"), i));
    sendCommand(CMD_RELAY_00 + i);
}

auto TempCtrlRelay::getRelayState(uint8_t i) -> int
{
    if (i >= relayMax) {
        return -1;
    }
    if (!relayControl[i].enabled) {
        return RELAY_DISABLED;
    }
    return relayControl[i].relay->isOn() ? RELAY_ON : RELAY_OFF;
}

void TempCtrlRelay::setRelayState(uint8_t i, uint8_t state)
{
    if (i >= relayMax) {
        return;
    }
    if (state == RELAY_DISABLED) {
        relayControl[i].enabled = false;
        relayControl[i].enabled.update();
        relayOff(i);
    } else if (state == RELAY_ON) {
        relayControl[i].enabled = true;
        relayControl[i].enabled.update();
        setMode(MODE_MANUAL);
        relayOn(i);
    } else if (state == RELAY_OFF) {
        relayControl[i].enabled = true;
        relayControl[i].enabled.update();
        setMode(MODE_MANUAL);
        relayOff(i);
    }
}

auto TempCtrlRelay::getRelayRangeOn(uint8_t i) -> float
{
    if (i >= relayMax) {
        return -1;
    }
    return relayControl[i].rangeOn;
}

auto TempCtrlRelay::getRelayRangeOff(uint8_t i) -> float
{
    if (i >= relayMax) {
        return -1;
    }
    return relayControl[i].rangeOff;
}

void TempCtrlRelay::setRelayRangeOn(uint8_t i, float value)
{
    if (i >= relayMax) {
        return;
    }
    relayControl[i].rangeOn = value;
    relayControl[i].rangeOn.update();
    sendCommand(CMD_RELAY_ON_00 + i);
    control();
}

void TempCtrlRelay::setRelayRangeOff(uint8_t i, float value)
{
    if (i >= relayMax) {
        return;
    }
    relayControl[i].rangeOff = value;
    relayControl[i].rangeOff.update();
    sendCommand(CMD_RELAY_OFF_00 + i);
    control();
}

void TempCtrlRelay::sendValues()
{
    TempCtrl::sendValues();
    for (int i = 0; i < relayMax; ++i) {
        if (relayControl[i].relay != nullptr) {
            sendCommand(CMD_RELAY_00 + i);
            sendCommand(CMD_RELAY_ON_00 + i);
            sendCommand(CMD_RELAY_OFF_00 + i);
        }
    }
}

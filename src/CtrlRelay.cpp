#include "../include/CtrlRelay.h"

CtrlRelay::CtrlRelay(RelayInterface *r) : relay(r), state(RELAY_OFF), init(0)
{
    init.restore();
    if (init != 1) {
        state.save();
        init = 1;
        init.save();
    } else {
        state.restore();
    }

    if (state == RELAY_ON) {
        relay->on();
        sendCommand(CMD_RELAY);
    } else if (state == RELAY_OFF) {
        relay->off();
        sendCommand(CMD_RELAY);
    }
    IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlRelay] Restore state: %d\n"), (uint8_t) state));
}

void CtrlRelay::addButton(Button *btn, uint8_t mode, uint8_t defaultAct)
{
    if (mode & MODE_ONE_BUTTON) {
        btn->addHandler(this, defaultAct);
        btn->addHandler(this, defaultAct != RELAY_OFF ? RELAY_OFF : RELAY_ON, Button::PRESSTIME_1SEC);
        buttons[0] = btn;
        IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlRelay::addButton] One button added. Default: %u\n"), defaultAct));
    }
    if (mode & MODE_ON) {
        btn->addHandler(this, RELAY_ON);
        buttons[0] = btn;
        IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlRelay::addButton] ON button added\n")));
    }
    if (mode & MODE_OFF) {
        btn->addHandler(this, RELAY_OFF);
        buttons[1] = btn;
        IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlRelay::addButton] OFF button added\n")));
    }
}

void CtrlRelay::sendValues()
{
    sendCommand(CMD_RELAY);
}

void CtrlRelay::call(uint8_t type, uint8_t idx)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[CtrlRelay::call] Type: %u, Index: %u \n"), type, idx));
    if (type == RELAY_ON) {
        relay->on();
        state = RELAY_ON;
        state.save();
        sendCommand(CMD_RELAY);
    } else if (type == RELAY_OFF) {
        relay->off();
        state = RELAY_OFF;
        state.save();
        sendCommand(CMD_RELAY);
    } else if (type == RELAY_CHANGE) {
        relay->change();
        state = relay->isOn() ? RELAY_ON : RELAY_OFF;
        state.save();
        sendCommand(CMD_RELAY);
    }
}

void CtrlRelay::tick()
{
    for (int i = 0; i < 2; ++i) {
        if (buttons[i] == nullptr) {
            continue;
        }
        buttons[i]->tick();
    }
}

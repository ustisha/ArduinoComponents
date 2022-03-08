#include "../include/LightController.h"

LightController::LightController() : timeout(60 * 1000),
                                     activityRatio(0.8),
                                     activityLimit(2),
                                     recallRatio(2.2),
                                     recallTimeout(2 * 1000),
                                     mode(MODE_AUTO),
                                     init(0),
                                     energyLvl(ENERGY_LVL_OFF),
                                     offTime(0),
                                     timeOff(0),
                                     activity(0) {

    init.restore();
    if (init != 1) {
        mode.save();
        timeout.save();
        activityRatio.save();
        activityLimit.save();
        recallRatio.save();
        recallTimeout.save();
        energyLvl.save();

        init = 1;
        init.save();
        IF_SERIAL_DEBUG(printf_P(PSTR("[LightController] Save default\n")));
    } else {
        mode.restore();
        timeout.restore();
        activityRatio.restore();
        activityLimit.restore();
        recallRatio.restore();
        recallTimeout.restore();
        energyLvl.restore();

        IF_SERIAL_DEBUG(printf_P(PSTR("[LightController] Restore values\n")));
    }

#ifdef SERIAL_DEBUG

    char actBuf[8];
    char reBuf[8];
    Format::floatVar(actBuf, activityRatio);
    Format::floatVar(reBuf, recallRatio);

    IF_SERIAL_DEBUG(
            printf_P(
                    PSTR("[LightController] Mode: %u, Timeout: %u, Act ratio: %s, Act limit: %u, Re ratio: %s, Re timeout: %u\n"),
                    (uint8_t) mode, (uint16_t) timeout, actBuf, (uint16_t) activityLimit, reBuf,
                    (uint16_t) recallTimeout));
#endif
}

void LightController::addMotion(Motion *pir) {
    pir->addHandler(this, TYPE_MOTION);
    pirs[pirIdx++] = pir;
    IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::addMotion] motion sensor added. Idx: %u\n"), pirIdx));
}

void LightController::addButton(Button *btn) {
    btn->addHandler(this, TYPE_AUTO);
    btn->addHandler(this, TYPE_ON, Button::PRESSTIME_1SEC);
    btn->addHandler(this, TYPE_OFF, Button::PRESSTIME_2SEC);
    modeButton = btn;
    IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::addButton] Control button added.\n")));
}

void LightController::call(uint8_t type, uint8_t idx) {
    IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::call] Type: %u, Index: %u \n"), type, idx));
    if (type == TYPE_AUTO) {
        timeOff = 0;
        setRelayState(RELAY_OFF);
        setMode(MODE_AUTO);
    } else if (type == TYPE_ON) {
        timeOff = 0;
        setRelayState(RELAY_ON);
        setMode(MODE_MANUAL);
    } else if (type == TYPE_OFF) {
        timeOff = 0;
        setRelayState(RELAY_OFF);
        setMode(MODE_MANUAL);
    } else if (type == TYPE_MOTION && mode == MODE_AUTO) {
        unsigned long m = millis();
        uint16_t currTimeout = timeout;
        if (energyLvl) {
            // Calc timeout in energy efficient mode
            currTimeout = lround(timeout / (energyLvl + 1));
            IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::call] Energy efficient. Mode: %u\n"), energyLvl));
        }
        uint32_t newTime = m + currTimeout;
        if (offTime != 0 && (m - offTime) < recallTimeout) {
            newTime += lround(currTimeout * recallRatio);
            IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::call] Recall raise\n")));
        } else if (activity >= 1) {
            if (activity > activityLimit) {
                activity = activityLimit;
            }
            newTime += lround(currTimeout * activityRatio * (float) activity);
            IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::call] Activity increase\n")));
        }

        // Use max time already set or new calculated.
        timeOff = max(timeOff, newTime);

        activity++;
        setRelayState(RELAY_ON);
    }
}

void LightController::setMode(uint8_t m) {
    mode = m;
    mode.save();
    sendCommand(CMD_MODE);
    if (mode == MODE_AUTO) {
        setRelayState(RELAY_OFF);
        resetValues();
    }
    render();
}

void LightController::setEnergyLevel(uint8_t lvl) {
    energyLvl = lvl;
    energyLvl.save();
    sendCommand(CMD_ENERGY_LEVEL);
    if (energyLvl == ENERGY_LVL2) {
        setMode(MODE_AUTO);
    }
    render();
}

void LightController::resetValues() {
    activity = 0;
    timeOff = 0;
    offTime = millis();
    sendCommand(CMD_TIME_LEFT);
    render();
    IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::tick] Reset values\n")));
}

void LightController::setTimeout(uint32_t t) {
    timeout = t;
    timeout.save();
    sendCommand(CMD_TIMEOUT);
}

void LightController::setActivityRatio(float ratio) {
    activityRatio = ratio;
    activityRatio.save();
    sendCommand(CMD_ACTIVITY_RATIO);
}

void LightController::setActivityLimit(uint16_t limit) {
    activityLimit = limit;
    activityLimit.save();
    sendCommand(CMD_ACTIVITY_LIMIT);
}

void LightController::setRecallRatio(float ratio) {
    recallRatio = ratio;
    recallRatio.save();
    sendCommand(CMD_RECALL_RATIO);
}

void LightController::setRecallTimeout(uint16_t t) {
    recallTimeout = t;
    recallTimeout.save();
    sendCommand(CMD_RECALL_TIMEOUT);
}

void LightController::setRelayState(uint8_t state) {
    if (state == RELAY_ON) {
        relay->on();
    } else if (state == RELAY_OFF) {
        relay->off();
    }
    sendCommand(CMD_RELAY_00);
    render();
}

void LightController::setState(uint8_t state) {
    setRelayState(state);
    setMode(MODE_MANUAL);
}

long LightController::getOffTime() const {
    return timeOff > 0 ? lround((timeOff - millis()) / 1000) : 0;
}

void LightController::tick() {
    if (modeButton != nullptr) {
        modeButton->tick();
    }

    if (mode == MODE_MANUAL) {
        return;
    }
    for (uint8_t b = 0; b < pirIdx; b++) {
        pirs[b]->tick();
    }
    unsigned long m = millis();

    if (timeOff != 0) {
        if (((timeOff - m) % 10000) == 0) {
            sendCommand(CMD_TIME_LEFT);
        }
        if ((m % 1000) == 0) {
            render();
#ifdef SERIAL_DEBUG
            long off = getOffTime();
            IF_SERIAL_DEBUG(printf_P(PSTR("[LightController::tick] Left: %ld\n"), off));
#endif
        }
        if (m > timeOff) {
            setRelayState(RELAY_OFF);
            resetValues();
        }
    }
}

void LightController::sendValues() {
    sendCommand(CMD_MODE);
    sendCommand(CMD_RELAY_00);
    sendCommand(CMD_TIMEOUT);
    sendCommand(CMD_ACTIVITY_RATIO);
    sendCommand(CMD_ACTIVITY_LIMIT);
    sendCommand(CMD_RECALL_RATIO);
    sendCommand(CMD_RECALL_TIMEOUT);
    sendCommand(CMD_ENERGY_LEVEL);
}

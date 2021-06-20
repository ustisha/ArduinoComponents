#include "../include/TempCtrl.h"

TempCtrl::TempCtrl(THInterface *tiface, float down, float up) :
        downLimit(down),
        upLimit(up),
        mode(MODE_AUTO),
        timeout(60000),
        init(0)
{

    init.restore();
    if (init != 1) {
        downLimit.save();
        upLimit.save();
        mode.save();
        timeout.save();
    } else {
        downLimit.restore();
        upLimit.restore();
        mode.restore();
        timeout.restore();
    }

    last = millis();

#ifdef SERIAL_DEBUG
    static char dlBuf[8];
    static char ulBuf[8];
    Format::floatVar(dlBuf, downLimit);
    Format::floatVar(ulBuf, upLimit);

    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrl::TempCtrl] Mode: %d, Down limit: %s, Up limit: %s\n"),
                             (int) mode,
                             dlBuf,
                             ulBuf));
#endif
}

void TempCtrl::tick(uint16_t sleep)
{
    if (mode != MODE_AUTO) {
        return;
    }

    sleepTime += sleep;
    unsigned long m;
    m = millis() + sleepTime;
    if (m >= (last + timeout) || last < timeout) {
        last += timeout;
        control();
    }
}

void TempCtrl::setMode(uint8_t m)
{
    mode = m;
    mode.save();
    if (mode == MODE_AUTO) {
        control();
    } else if (mode == MODE_MANUAL) {

    }
    sendCommand(CMD_MODE);
}

void TempCtrl::setDownLimit(float limit)
{
    downLimit = limit;
    downLimit.save();
    if (mode == MODE_AUTO) {
        control();
    }
    sendCommand(CMD_DOWN_LIMIT);
}

void TempCtrl::setUpLimit(float limit)
{
    upLimit = limit;
    upLimit.save();
    if (mode == MODE_AUTO) {
        control();
    }
    sendCommand(CMD_UP_LIMIT);
}

void TempCtrl::setTimeout(uint16_t t)
{
    timeout = t * 1000;
    timeout.save();
    if (mode == MODE_AUTO) {
        control();
    }
    sendCommand(CMD_TIMEOUT);
}

void TempCtrl::sendValues()
{
    sendCommand(CMD_MODE);
    sendCommand(CMD_UP_LIMIT);
    sendCommand(CMD_DOWN_LIMIT);
    sendCommand(CMD_TIMEOUT);
}

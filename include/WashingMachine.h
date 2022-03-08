#ifndef WASHINGMACHINE_H
#define WASHINGMACHINE_H

#include <Arduino.h>
#include <DebugLog.h>
#include <DisplayHandler.h>

class WashingMachine : public DisplayHandler
{

public:

    WashingMachine() = default;

    const static uint8_t OFF = 0;
    const static uint8_t READY = 1;
    const static uint8_t RUN = 2;
    const static uint8_t FINISHED = 3;
    const static uint8_t ERR = 4;

    bool doorOpened = false;
    int8_t state = OFF;
    int16_t remainingSec = 0;
};

#endif //WASHINGMACHINE_H

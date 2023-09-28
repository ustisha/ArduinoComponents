#include "../include/ValueInt.h"

ValueInt::ValueInt() : init(0), inputMin(0), inputMax(100)
{
    init.restore();
    if (init != 1) {
        inputMin.save();
        inputMax.save();
        init = 1;
        init.save();
    } else {
        inputMin.restore();
        inputMax.restore();
    }
}

void ValueInt::setInputMin(int16_t inMin)
{
    inputMin = inMin;
    inputMin.save();
    sendCommand(CMD_MAP_MIN);
    read();
    sendCommand(CMD_VALUE);
}

void ValueInt::setInputMax(int16_t inMax)
{
    inputMax = inMax;
    inputMax.save();
    sendCommand(CMD_MAP_MAX);
    read();
    sendCommand(CMD_VALUE);
}

void ValueInt::setOutputValues(int16_t outMin, int16_t outMax)
{
    useMap = true;
    outputMin = outMin;
    outputMax = outMax;
}

void ValueInt::sendValues()
{
    sendCommand(CMD_VALUE);
    sendCommand(CMD_MAP_MIN);
    sendCommand(CMD_MAP_MAX);
}

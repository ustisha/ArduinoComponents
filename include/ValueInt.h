#ifndef VALUEINT_H
#define VALUEINT_H

#include <Arduino.h>
#include <DebugLog.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>
#include <ValueIntInterface.h>
#include <NetInterface.h>

class ValueInt : public ValueIntInterface, NetInterface
{

public:
    using NetInterface::addNet;

    EEPROMVar<uint8_t> init;
    EEPROMVar<int16_t> inputMin;
    EEPROMVar<int16_t> inputMax;

    ValueInt() : init(0), inputMin(0), inputMax(100)
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

    void setInputMin(int16_t inMin)
    {
        inputMin = inMin;
        inputMin.save();
        sendCommand(CMD_MAP_MIN);
        read();
        sendCommand(CMD_VALUE);
    }

    void setInputMax(int16_t inMax)
    {
        inputMax = inMax;
        inputMax.save();
        sendCommand(CMD_MAP_MAX);
        read();
        sendCommand(CMD_VALUE);
    }

    void setOutputValues(int16_t outMin = 0, int16_t outMax = 100)
    {
        useMap = true;
        outputMin = outMin;
        outputMax = outMax;
    }

    void sendValues()
    {
        sendCommand(CMD_VALUE);
        sendCommand(CMD_MAP_MIN);
        sendCommand(CMD_MAP_MAX);
    }

    void set(long v)
    {
        value = v;
    }

    long getRaw()
    {
        read();
        return rawValue;
    }

protected:
    int16_t outputMax = 0, outputMin = 0;
    long rawValue = 0;
    bool useMap = false;

    int read() override
    {};
};


#endif //VALUEINT_H

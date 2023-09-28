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
    using NetInterface::sendCommand;

    EEPROMVar<uint8_t> init;
    EEPROMVar<int16_t> inputMin;
    EEPROMVar<int16_t> inputMax;

    ValueInt();

    void setInputMin(int16_t inMin);

    void setInputMax(int16_t inMax);

    void setOutputValues(int16_t outMin = 0, int16_t outMax = 100);

    void sendValues();

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

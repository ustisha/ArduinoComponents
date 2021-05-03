#ifndef ANALOGREADER_H
#define ANALOGREADER_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <ValueIntInterface.h>

class AnalogReader : public ValueIntInterface
{
public:
    AnalogReader(uint8_t p);

    int read() override;

    void setMapValues(int32_t inMin, int32_t inMax, int32_t outMin = 0, int32_t outMax = 100)
    {
        useMap = true;
        inputMin = inMin;
        inputMax = inMax;
        outputMin = outMin;
        outputMax = outMax;
    }

protected:
    bool useMap = false;
    int32_t inputMax, inputMin, outputMax, outputMin;
    uint8_t pin;
};

#endif //ANALOGREADER_H

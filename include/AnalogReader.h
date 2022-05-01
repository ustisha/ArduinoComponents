#ifndef ANALOGREADER_H
#define ANALOGREADER_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <ValueInt.h>

class AnalogReader : public ValueInt
{
public:
    explicit AnalogReader(uint8_t p);

    int read() override;

protected:
    uint8_t pin;
};

#endif //ANALOGREADER_H

#include "../include/AnalogReader.h"

AnalogReader::AnalogReader(uint8_t p) : ValueInt(), pin(p)
{
    pinMode(pin, INPUT);
}

int AnalogReader::read()
{
    value = rawValue = analogRead(pin);
    IF_SERIAL_DEBUG(printf_P(PSTR("[AnalogReader::read] Value: %d\n"), value));
    if (useMap) {
        value = (value - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
        IF_SERIAL_DEBUG(printf_P(PSTR("[AnalogReader::read] Map value: %d\n"), value));
    }
    return value;
}

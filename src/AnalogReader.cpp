#include "../include/AnalogReader.h"

AnalogReader::AnalogReader(uint8_t p) : pin(p) {
    pinMode(pin, INPUT);
}

int AnalogReader::read() {
    int v = analogRead(pin);
    IF_SERIAL_DEBUG(printf_P(PSTR("[AnalogReader::read] Value: %d\n"), v));
    if (useMap) {
        v = (v - inputMin) * (outputMax - outputMin) / (inputMax - inputMin) + outputMin;
        IF_SERIAL_DEBUG(printf_P(PSTR("[AnalogReader::read] Map value: %d\n"), v));
    }
    return v;
}

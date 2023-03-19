#include "../include/BinaryReader.h"

BinaryReader::BinaryReader(uint8_t p, bool invert) : ValueInt(), pin(p)
{
    pinMode(pin, INPUT);
    invt = invert;
}

int BinaryReader::read()
{
    value = rawValue = invt ? !digitalRead(pin) : digitalRead(pin);
    IF_SERIAL_DEBUG(printf_P(PSTR("[BinaryReader::read] Value: %d\n"), value));
    return value;
}

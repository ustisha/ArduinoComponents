#include "../include/BinaryReader.h"

BinaryReader::BinaryReader(uint8_t p, bool invert) : ValueInt(), pin(p), start(0)
{
    pinMode(pin, INPUT);
    invt = invert;
}

int BinaryReader::read()
{
    value = rawValue = invt ? !digitalRead(pin) : digitalRead(pin);
    return value;
}

void BinaryReader::tick()
{
    unsigned long m = millis();
    int currentRead = read();

    if (start == 0 && currentState != currentRead) {
        start = m;
        IF_SERIAL_DEBUG(printf_P(PSTR("[BinaryReader::tick] Start timer\n")));
        return;
    }

    if (currentState == currentRead) {
        start = 0;
        return;
    }

    if (start != 0 && (m - start) > BinaryReader::CHANGE_DEFAULT) {
        currentState = currentRead;
        start = 0;
        sendCommand(CMD_VALUE);
        IF_SERIAL_DEBUG(printf_P(PSTR("[BinaryReader::tick] State changed\n")));
        return;
    }
}

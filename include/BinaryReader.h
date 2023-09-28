#ifndef BINARYREADER_H
#define BINARYREADER_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <ValueInt.h>

class BinaryReader : public ValueInt
{
public:
    static const uint16_t CHANGE_DEFAULT = 10;

    explicit BinaryReader(uint8_t p, bool invert);

    int read() override;

    void tick();

protected:
    uint8_t pin;
    int currentState = 0;
    bool invt = false;
    unsigned long start;
};

#endif //BINARYREADER_H

#ifndef BINARYREADER_H
#define BINARYREADER_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <ValueInt.h>

class BinaryReader : public ValueInt
{
public:
    explicit BinaryReader(uint8_t p, bool invert);

    int read() override;

protected:
    uint8_t pin;
    bool invt = false;
};

#endif //BINARYREADER_H

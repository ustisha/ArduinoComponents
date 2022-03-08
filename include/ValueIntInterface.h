#ifndef VALUEINTERFACE_H
#define VALUEINTERFACE_H

#include <Arduino.h>
#include <DebugLog.h>
#include <DisplayHandler.h>

class ValueIntInterface: public DisplayHandler {

public:

    long get() {
        this->read();
        return value;
    }

protected:

    long value = 0;

    virtual int read() = 0;
};

#endif //VALUEINTERFACE_H

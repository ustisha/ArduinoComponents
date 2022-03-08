#ifndef VALUEINT_H
#define VALUEINT_H

#include <Arduino.h>
#include <DebugLog.h>
#include <ValueIntInterface.h>

class ValueInt : public ValueIntInterface
{

public:

    void set(long v)
    {
        value = v;
    }

protected:
    int read() override {};
};


#endif //VALUEINT_H

#ifndef TVIRTUAL_H
#define TVIRTUAL_H

#include <Arduino.h>
#include <TInterface.h>

class TVirtual : public TInterface
{

public:

    void set(float t)
    {
        temp = t;
    }

    void setStatus(int s)
    {
        status = s;
    }

    void read() override
    {

    }

protected:
};

#endif //TVIRTUAL_H

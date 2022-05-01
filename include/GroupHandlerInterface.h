#ifndef GROUPHANDLERINTERFACE_H
#define GROUPHANDLERINTERFACE_H

#include <Arduino.h>
#include <HandlerInterface.h>

class GroupHandlerInterface : public HandlerInterface
{
public:
    virtual void syncMode(uint8_t mode) = 0;

    virtual void syncMode() = 0;

};

#endif //GROUPHANDLERINTERFACE_H

#ifndef MOTIONCTRL_H
#define MOTIONCTRL_H

#include <Arduino.h>
#include <DebugLog.h>
#include <Motion.h>
#include <NetInterface.h>

class MotionCtrl : public Motion, NetInterface
{
public:
    using Motion::Motion;
    using NetInterface::addNet;

    void setState(bool state) override
    {
        Motion::setState(state);
        sendCommand(CMD_MOTION);
    }

    void sendValues()
    {
        sendCommand(CMD_MOTION);
    }
};

#endif //MOTIONCTRL_H

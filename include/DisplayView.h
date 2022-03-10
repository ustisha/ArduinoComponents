#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Format.h>
#include <LightController.h>
#include <THInterface.h>

class DisplayView
{

public:

    void addModule(THInterface *thInterface);

    void addModule(LightController *lightController);

    virtual void render() = 0;

protected:

    static const uint8_t MAX_LIGHT_CONTROLLER = 2;
    static const uint8_t MAX_TH = 1;

    template<typename T>
    struct ValueUpdate
    {
        bool rendered = false;
        T value = 0;
    };

    struct ThUpdate : public ValueUpdate<float>
    {
        float value2 = 0;
    };

    struct LightUpdate : public ValueUpdate<uint8_t>
    {
        uint8_t mode = 255;
        int16_t timeout = 0;
        uint8_t energyLvl = 0;
    };


    LightController *light[MAX_LIGHT_CONTROLLER]{};
    THInterface *th[MAX_TH]{};
    ThUpdate thUpdate[MAX_TH];
    LightUpdate lightUpdate[MAX_LIGHT_CONTROLLER];
    uint8_t thIdx = 0, lIdx = 0;
};

#endif //DISPLAYVIEW_H

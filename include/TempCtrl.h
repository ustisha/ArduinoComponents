#ifndef TEMPCTRL_H
#define TEMPCTRL_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <THInterface.h>
#include <NetInterface.h>
#include <NetComponent.h>
#include <Relay.h>
#include <Button.h>
#include <Format.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

class TempCtrl : public NetInterface, virtual public HandlerInterface
{

public:
    // 1 бит - Открывать при понижении значения нижней границы
    // 2 бит - Открывать при превышении значения верхней границы
    // 3 бит - Открывать при понижении значения ниже верхней границы
    // 4 бит - Открывать при превышении значения выше нижней границы
    const static uint8_t TYPE_BELOW_DOWN_LIMIT = B00000001;
    const static uint8_t TYPE_ABOVE_UP_LIMIT = B00000010;
    const static uint8_t TYPE_BELOW_UP_LIMIT = B00000100;
    const static uint8_t TYPE_ABOVE_DOWN_LIMIT = B00001000;
    // 7 бит - Использовать показаия влажности
    const static uint8_t TYPE_HUMIDITY = B01000000;
    // 8 бит - Использовать показаия температуры
    const static uint8_t TYPE_TEMPERATURE = B10000000;

    EEPROMVar<float> downLimit;
    EEPROMVar<float> upLimit;
    EEPROMVar<uint8_t> mode;
    EEPROMVar<uint32_t> timeout;
    EEPROMVar<uint8_t> init;

    TempCtrl(THInterface *tiface, float down, float up);

    virtual void tick(uint16_t sleep);

    void setDownLimit(float limit);

    float getDownLimit()
    {
        return downLimit;
    }

    void setUpLimit(float limit);

    float getUpLimit()
    {
        return upLimit;
    }

    void setMode(uint8_t m);

    void setTimeout(uint16_t t);

    virtual void sendValues();

    void initDone()
    {
        if (init != 1) {
            init = 1;
            init.save();
        }
    }

    virtual void call(uint8_t type, uint8_t idx) = 0;

protected:

    virtual void control() = 0;

    unsigned long sleepTime = 0;
    unsigned long last;
};


#endif //TEMPCTRL_H

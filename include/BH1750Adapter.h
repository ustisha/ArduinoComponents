#ifndef BHLIGHT_H
#define BHLIGHT_H

//#define SERIAL_DEBUG
//#define NON_BLOCKING

#include <Arduino.h>
#include <DebugLog.h>
#include <Format.h>
#include <hp_BH1750.h>
#include <LightSensorInterface.h>

class BH1750Adapter : public LightSensorInterface
{
public:
    explicit BH1750Adapter(BH1750Address mode);

    void read() override;

    auto getStatus() -> int
    {
        return status;
    }

#ifdef NON_BLOCKING

    void tick();

#endif

protected:
    hp_BH1750 *bh;
    int status = 0;
#ifdef NON_BLOCKING
    bool reading = false;
#endif

    auto getLuxInternal() -> float;
};

#endif //BHLIGHT_H

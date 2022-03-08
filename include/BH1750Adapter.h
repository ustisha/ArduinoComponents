#ifndef BHLIGHT_H
#define BHLIGHT_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <hp_BH1750.h>
#include <LightSensorInterface.h>

class BH1750Adapter : public LightSensorInterface {
public:
    explicit BH1750Adapter(BH1750Address mode);

    void read() override;

    auto getStatus() -> int;

protected:
    hp_BH1750 *bh;
    int status = 0;
};

#endif //BHLIGHT_H

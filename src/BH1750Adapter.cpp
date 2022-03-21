#include "../include/BH1750Adapter.h"

BH1750Adapter::BH1750Adapter(BH1750Address mode)
{
    bh = new hp_BH1750();
    status = (int) bh->begin(mode);
    bh->setQuality(BH1750Quality::BH1750_QUALITY_HIGH);
    IF_SERIAL_DEBUG(printf_P(PSTR("[BH1750Adapter] Status: %d\n"), status));
}

auto BH1750Adapter::getLuxInternal() -> float
{
    float lux = bh->getLux();
#ifdef SERIAL_DEBUG
    char buffer[10]{};
    Format::floatVar(buffer, lux);
    IF_SERIAL_DEBUG(printf_P(PSTR("[BH1750Adapter::read] Lux: %s\n"), buffer));
#endif
    return lux;
}

#ifdef NON_BLOCKING

void BH1750Adapter::read()
{
    reading = true;
    bh->start();
    IF_SERIAL_DEBUG(printf_P(PSTR("[BH1750Adapter::read] Read started\n")));
}

void BH1750Adapter::tick()
{
    if (bh->hasValue()) {
        light = getLuxInternal();
    }
}

#else

void BH1750Adapter::read()
{
    bh->start();
    light = getLuxInternal();
}

#endif

#include "../include/BH1750Adapter.h"

BH1750Adapter::BH1750Adapter(BH1750Address mode) {
    bh = new hp_BH1750();
    status = (int) bh->begin(mode);
}

void BH1750Adapter::read() {
    light = bh->getLux();

#ifdef SERIAL_DEBUG
    String l(light);
    static char buffer[10];
    l.toCharArray(buffer, 10);

    IF_SERIAL_DEBUG(printf_P(PSTR("[BH1750Adapter::read] Lux: %s\n"), buffer));
#endif
}

int BH1750Adapter::getStatus() {
    return status;
}


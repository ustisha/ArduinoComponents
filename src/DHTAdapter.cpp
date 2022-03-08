#include <../include/DHTAdapter.h>

DHTAdapter::DHTAdapter(uint8_t pin, uint8_t type)
{
    dht = new DHT(pin, type);
    dht->begin();
    status = 1;
    IF_SERIAL_DEBUG(printf_P(PSTR("[DHTAdapter] Begin initialized, pin: %d, type: %d\n"), pin, type));
}

void DHTAdapter::read()
{
    temp = dht->readTemperature();
    hum = dht->readHumidity();
    if (isnan(temp) || isnan(hum)) {
        status = -1;
        IF_SERIAL_DEBUG(printf_P(PSTR("[DHTAdapter::tick] Is nan return\n")));
        return;
    }
    status = 1;
    render();

#ifdef SERIAL_DEBUG
    char tBuf[8]{};
    Format::floatVar(tBuf, temp);
    char hBuf[8]{};
    Format::floatVar(hBuf, hum);
    IF_SERIAL_DEBUG(printf_P(PSTR("[DHTAdapter::tick] Read done. Temp: %s, Hum: %s\n"), tBuf, hBuf));
#endif
}

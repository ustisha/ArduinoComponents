#include <Format.h>
#include "../include/BME280Adapter.h"

BME280Adapter::BME280Adapter(TwoWire &wire, uint8_t address) {
    bme = new Adafruit_BME280();
    status = bme->begin(address, &wire);
    bme->setSampling(Adafruit_BME280::sensor_mode::MODE_FORCED,
                     Adafruit_BME280::sensor_sampling::SAMPLING_X16,
                     Adafruit_BME280::sensor_sampling::SAMPLING_X16,
                     Adafruit_BME280::sensor_sampling::SAMPLING_X16,
                     Adafruit_BME280::sensor_filter::FILTER_OFF,
                     Adafruit_BME280::standby_duration::STANDBY_MS_10);
    IF_SERIAL_DEBUG(printf_P(PSTR("[BME280Adapter] Begin status: %d\n"), status));
}

void BME280Adapter::read() {
    bme->takeForcedMeasurement();

    temp = bme->readTemperature();
    hum = bme->readHumidity();
    pressure = bme->readPressure();

#ifdef SERIAL_DEBUG
    char tBuf[8]{};
    Format::floatVar(tBuf, temp);
    char hBuf[8]{};
    Format::floatVar(hBuf, hum);
    char pBuf[10]{};
    Format::floatVar(pBuf, pressure);
    IF_SERIAL_DEBUG(printf_P(PSTR("[BME280Adapter::read] Temp: %s, Hum: %s, Pressure %s\n"), tBuf, hBuf, pBuf));
#endif
}

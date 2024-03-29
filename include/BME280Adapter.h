#ifndef BMETEMPHUMPRESSURE_H
#define BMETEMPHUMPRESSURE_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <THPInterface.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

class BME280Adapter : public THPInterface {

public:
    BME280Adapter(TwoWire &wire, uint8_t address);

    void read() override;

protected:
    Adafruit_BME280 *bme;
};

#endif //BMETEMPHUMPRESSURE_H

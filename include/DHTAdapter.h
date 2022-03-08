#ifndef DHTADAPTER_H
#define DHTADAPTER_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Format.h>
#include <THInterface.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

class DHTAdapter : public THInterface {

public:
    DHTAdapter(uint8_t pin, uint8_t type);

    void read() override;

protected:
    DHT *dht;
};


#endif // DHTADAPTER_H

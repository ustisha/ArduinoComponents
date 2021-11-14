#ifndef DHTADAPTER_H
#define DHTADAPTER_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Format.h>
#include <THInterface.h>
#include <dht_nonblocking.h>
#include <GyverFilters.h>

class DHTAdapter : public THInterface {

public:
    DHTAdapter(uint8_t pin, uint8_t type);

    void read() override;

    void tick();

protected:
    bool reading = false;
    DHT_nonblocking *dht;
    GMedian3<float> tempFilter, humFilter;
};


#endif // DHTADAPTER_H

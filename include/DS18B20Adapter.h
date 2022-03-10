#ifndef ONEWIRETEMPERATURE_H
#define ONEWIRETEMPERATURE_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Format.h>
#include <TVirtual.h>
#include <DallasTemperature.h>

// Sensor dont support humidity measure but this need for TempCtrlRelay compatible.
class DS18B20Adapter : public TVirtual {
public:
    DS18B20Adapter(OneWire *oneWire, byte idx);

    void read() override;
    
protected:
    DallasTemperature *sensors;
    byte addressIdx;
};

#endif //ONEWIRETEMPERATURE_H

#ifndef TEMPHUM_H
#define TEMPHUM_H

#include <Arduino.h>
#include <TInterface.h>
#include <Median3.h>

class THInterface : public TInterface {

public:

    float getHumidity() {
        return hum;
    }

protected:
    Median3<float> humFilter;
    float hum{};
};

#endif //TEMPHUM_H

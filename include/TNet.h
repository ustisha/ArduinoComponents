#ifndef TEMPNET_H
#define TEMPNET_H

#include <Arduino.h>
#include <TVirtual.h>
#include <NetComponent.h>

class TNet : public NetComponent {

public:
    TNet(SmartNet *n, uint8_t sp, uint8_t max, TVirtual *t) : NetComponent(n, sp, max) {
        temperature = t;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

protected:
    TVirtual *temperature;

    void receiveCommandData(Packet *p) override;

};

#endif //TEMPNET_H

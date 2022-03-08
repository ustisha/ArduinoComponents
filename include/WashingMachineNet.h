#ifndef WASHINGMACHINENET_H
#define WASHINGMACHINENET_H

#include <Arduino.h>
#include <WashingMachine.h>
#include <NetComponent.h>

class WashingMachineNet : public NetComponent {

public:
    WashingMachineNet(SmartNet *n, uint8_t sp, uint8_t max, WashingMachine *w) : NetComponent(n, sp, max) {
        washing = w;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override {};

protected:
    WashingMachine *washing;

    void receiveCommandData(Packet *p) override;

};

#endif //WASHINGMACHINENET_H

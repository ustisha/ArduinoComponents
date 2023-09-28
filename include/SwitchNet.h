#ifndef SWITCHNET_H
#define SWITCHNET_H

#include <Arduino.h>
#include <SwitchCtrl.h>
#include <NetComponent.h>

class SwitchNet : public NetComponent {

public:
    SwitchNet(SmartNet *n, uint8_t sp, uint8_t max, SwitchCtrl *b) : NetComponent(n, sp, max) {
        buttonCtrl = b;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

protected:
    SwitchCtrl *buttonCtrl;

    /**
     * Realisation not needed.
     * @param cmd
     * @param data
     */
    void receiveCommandData(Packet *p) override;
};

#endif //SWITCHNET_H

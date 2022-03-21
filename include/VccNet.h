#ifdef defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) \
|| defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined (__AVR_ATtiny25__) \
|| defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)

#ifndef VCCNET_H
#define VCCNET_H

#include <Arduino.h>
#include <SmartNet.h>
#include <NetComponent.h>
#include <Vcc.h>

class VccNet : public NetComponent {
    using NetComponent::NetComponent;
public:
    VccNet(SmartNet *n, uint8_t sp, uint8_t max, Vcc *v) : NetComponent(n, sp, max) {
        vcc = v;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

protected:
    Vcc *vcc;

    /**
     * Realisation not needed.
     * @param cmd
     * @param data
     */
    void receiveCommandData(Packet *p) override {};
};


#endif //VCCNET_H
#endif
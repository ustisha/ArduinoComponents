#ifndef MOTIONNET_H
#define MOTIONNET_H

#include <Arduino.h>
#include <MotionCtrl.h>
#include <NetComponent.h>

class MotionNet : public NetComponent {

public:
    MotionNet(SmartNet *n, uint8_t sp, uint8_t max, MotionCtrl *m) : NetComponent(n, sp, max) {
        motion = m;
    }

    void sendCommandData(RadioInterface *n, uint8_t r, uint8_t rp, uint8_t cmd) override;

protected:
    MotionCtrl *motion;

    /**
     * Realisation not needed.
     * @param cmd
     * @param data
     */
    void receiveCommandData(Packet *p) override;
};

#endif //MOTIONNET_H

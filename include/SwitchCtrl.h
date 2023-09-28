#ifndef SWITCHCTRL_H
#define SWITCHCTRL_H

#include <Arduino.h>
#include <Switch.h>
#include <NetInterface.h>

class SwitchCtrl : public Switch, NetInterface, virtual public HandlerInterface
{
public:
    uint8_t lastType = 0;

    using Switch::Switch;

    void addNet(RadioInterface *radioInterface, NetComponent *netCmp, uint8_t receiver, uint8_t receiverPort);

    void call(uint8_t type, uint8_t idx) override;

    void sendValues();
};

#endif //SWITCHCTRL_H

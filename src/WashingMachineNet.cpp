#include "WashingMachineNet.h"

void WashingMachineNet::receiveCommandData(Packet *p)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[WashingMachineNet::receiveCommandData] Cmd: %i, Data: %ld\n"),
                             p->getCommand(),
                             p->getData()));

    if (p->getCommand() == CMD_WASHING_STATE) {
        washing->state = p->getData();
        washing->render();
    } else if (p->getCommand() == CMD_WASHING_DOOR_OPENED) {
        washing->doorOpened = p->getData();
        washing->render();
    } else if (p->getCommand() == CMD_WASHING_REMAINING_SEC) {
        washing->remainingSec = p->getData();
        washing->render();
    }
}

#include <TempCtrlGroup.h>

TempCtrlGroup::TempCtrlGroup(uint8_t tempMax) :
        tempControls(new TempControls[tempMax]{}), tMax(tempMax), groupMode(0)
{

}

void TempCtrlGroup::addTempCtrl(TempCtrl *tempCtrl, uint8_t idx)
{
    tempCtrl->addGroupHandler(this, idx);
    tempControls[idx].ctrl = tempCtrl;
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlGroup::addTempCtrl] Added: %u\n"), idx));
    syncMode();
}

void TempCtrlGroup::syncMode()
{
    uint8_t groupCount = 0;
    int16_t group = -1;
    for (int i = 0; i < tMax; i++) {
        if (tempControls[i].ctrl != nullptr) {
            groupCount++;
            if (group == -1) {
                group = tempControls[i].ctrl->mode;
            } else if (group != tempControls[i].ctrl->mode) {
                group = MODE_MANUAL;
                break;
            }
        }
    }
    if (groupCount > 1) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlGroup::syncMode] Mode synced. Group: %d\n"), group));
        groupMode = group;
        sendCommand(CMD_MODE);
    }
}

void TempCtrlGroup::syncMode(uint8_t mode)
{
    groupMode = mode;
    for (int i = 0; i < tMax; i++) {
        if (tempControls[i].ctrl != nullptr && tempControls[i].ctrl->mode != mode) {
            IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlGroup::syncMode] Idx: %d, Mode: %u\n"), i, mode));
            tempControls[i].ctrl->setMode(mode);
        }
    }
    sendCommand(CMD_MODE);
}

void TempCtrlGroup::call(uint8_t type, uint8_t idx)
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TempCtrlGroup::call] Type: %u, Idx: %u\n"), type, idx));
}

void TempCtrlGroup::sendValues()
{
    sendCommand(CMD_MODE);
}

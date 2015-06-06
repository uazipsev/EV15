#include "DDS_Interface.h"

bool seekButtonChange() {
    int i = 0;
    bool changeInButton = false;
    for (i = 0; i < 8; i++) {
        bool buttonState=((buttons >> i)&(0x01));
        if (buttonArray[i] != buttonState) {
            buttonArray[i] = buttonState;
            changeInButton = true;
        }
    }
    return changeInButton;
}

void changeLEDState(int LED, bool state) {
    if(state)
    indicators = indicators | (state << LED);
    else
        indicators = indicators & (0xFF^(!state<<LED));
}
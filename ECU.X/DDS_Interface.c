#include "DDS_Interface.h"

bool seekButtonChange(){
    int i=0;
    bool changeInButton=false;
    for(i=0;i<8;i++){
        if(buttonArray[i]!=(buttons&(0x01<<i))){
        buttonArray[i]=buttons&(0x01<<i);
        changeInButton=true;
        }
    }
    return changeInButton;
}

void changeLEDState(int LED,bool state){
    indicators=indicators|(state<<LED);
}
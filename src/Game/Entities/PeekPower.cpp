#include "PeekPower.h"

bool PeekMode = false;
void PeekPower::activate() {
    PeekMode = true;
}

PeekPower::PeekPower(bool inPossession) : PowerUp(inPossession){
    
}

#include "RandomPowerUp.h"

bool RandomOn = false;
void RandomPowerUp::activate() {
    RandomOn = true;
}

RandomPowerUp::RandomPowerUp(bool inPossession) : PowerUp(inPossession){
    
}


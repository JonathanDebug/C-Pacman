#pragma once
#include "PowerUp.h"
#include "Dot.h"
#include "EntityManager.h"
extern bool RandomOn;
class RandomPowerUp : public PowerUp{
    public:
        void activate();
        RandomPowerUp(bool inPossession);
    private:
        EntityManager* em;
};
#pragma once
#include "PowerUp.h"

extern bool PeekMode;

class PeekPower : public PowerUp {
    public:
        void activate();
        PeekPower(bool inPossession);
};
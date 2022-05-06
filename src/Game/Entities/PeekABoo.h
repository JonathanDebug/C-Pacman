#pragma once
#include "Ghost.h"
#include "Player.h"
extern bool PeekEnabled;
class PeekABoo : public Ghost{
    private:
        bool inRange = false;
    public:
        PeekABoo(int x, int y, int width, int height, ofImage spritesheet, EntityManager* em, string color);
        ~PeekABoo();
        void render() override;
        void setinRange(bool inRange);
};



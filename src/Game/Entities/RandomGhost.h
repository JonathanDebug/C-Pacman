#pragma once
#include "Ghost.h"
#include "Dot.h"
extern bool RandomEnabled;
class RandomGhost : public Ghost{
    public:
        RandomGhost(int width, int height, ofImage spritesheet, EntityManager* em, string color,Entity* player);
    private:
        Entity* player;
        
    
        

};
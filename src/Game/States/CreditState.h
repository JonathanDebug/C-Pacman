#pragma once
#include "GameState.h"

class CreditState : public GameState{
    public:
        CreditState();
        void render();
        void tick();
        void reset();
    private:
        ofImage scene;
        ofSoundPlayer music;

    

};
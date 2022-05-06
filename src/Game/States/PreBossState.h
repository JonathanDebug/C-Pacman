#pragma once
#include "GameState.h"
#include "Button.h"
class PreBossState : public GameState{
    public:
        PreBossState();
        ~PreBossState();
        void tick();
        void render();
	    void reset();
        void mousePressed(int x, int y, int button);

    private:
        ofImage image;
        Button *yesButton;
        Button *LeaveButton;
};
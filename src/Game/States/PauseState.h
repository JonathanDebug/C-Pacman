#pragma once
#include "State.h"
#include "Player.h"
#include "Button.h"

extern bool Paused;

class PauseState : public State
{
    private:
        Button* resume;
        Button* quit;
        ofImage PauseImage;
        bool wasPaused=false;
        ofSoundPlayer music;
        ofImage resumeButton;
        ofImage quitButton;
        ofImage background;
        ofImage PauseControls;
    public:
        PauseState();
        ~PauseState();
        void tick();
	    void render();
	    void keyPressed(int key);
	    void mousePressed(int x, int y, int button);
        void reset();
        bool getPaused();
        void setPaused(bool wasPaused);
    
};
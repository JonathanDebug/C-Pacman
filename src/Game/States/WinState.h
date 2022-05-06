#pragma once
#include "State.h"
#include "Button.h"


class WinState : public State{
    public:
        WinState();
        ~WinState();
        void tick();
        void render();
        void keyPressed(int key);
	    void mousePressed(int x, int y, int button);
	    void reset();
	    void setScore(int);

    private:
	    Button *continueButton;
        Button *QuitButton;
	    int score=0;
        ofSoundPlayer music;
        ofImage Continue;
        ofImage Quit;
        ofImage background;
     



};
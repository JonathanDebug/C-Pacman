#pragma once
#include "GameState.h"
#include "Button.h"

class BossState: public GameState {
    public:
        BossState();
        ~BossState();
        void tick();
	    void render();
	    void mousePressed(int x, int y, int button);
	    void reset();
        void bossAtk(int atk);
        int chance(int num){return ofRandom(num);}
        void setTurn(bool turn){this->turn = turn;}
        void setHeal(bool heal){this->healingOn = heal;}
        void setMissed(bool miss){this->missed = miss;}
        void keyPressed(int key);
    private:
        ofImage stage;
        Button *fightButton;
        Button *healButton;
        Button *magicButton; 
        Button *superButton;
        int health = 150;
        int bossHealth = 300;
        int healpotions = 3;
        int superReady = 0; 
        bool turn;
        bool missed = false;
        int time = ofGetElapsedTimef();
        bool healingOn = true;
        ofSoundPlayer bossMusic;
       
};

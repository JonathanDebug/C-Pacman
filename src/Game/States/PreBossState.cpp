#include "PreBossState.h"
PreBossState::PreBossState(){
    image.load("images/PreBoss.jpg");
    this->yesButton = new Button(515, 641, 166, 68, "");
    this->LeaveButton = new Button(220, 641, 166, 68, "");
}


void PreBossState::tick() {
    yesButton->tick();
    LeaveButton->tick();

    if(yesButton->wasPressed()){
        setFinished(true);
        setNextState("Boss");
    }

    if(LeaveButton->wasPressed()){
        setFinished(true);
        setNextState("over");
    }
}

void PreBossState::render() {
    ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
    image.draw(ofGetWidth()/2 - image.getWidth()/2,ofGetHeight()/2 - image.getHeight()/2);
    yesButton->render();
    LeaveButton->render();
}


void PreBossState::reset(){
	setFinished(false);
	setNextState("");
    yesButton->reset();
    LeaveButton->reset();
}

void PreBossState::mousePressed(int x, int y, int button){
	yesButton->mousePressed(x, y);
    LeaveButton->mousePressed(x,y);
}



#include "CreditState.h"

CreditState::CreditState(){
    this->scene.load("images/credits.jpg");
    this->music.load("music/endsong.mp3");
}

void CreditState::tick(){
    int time = ofGetElapsedTimef();
    if(time >= 17){
        setNextState("Menu");
        setFinished(true);
    }

    if(!music.isPlaying()){
		ofSoundStopAll();
		music.play();
	}
}


void CreditState::render(){
    ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
    scene.draw(ofGetWidth()/2 - scene.getWidth()/2,ofGetHeight()/2 - scene.getHeight()/2);
}

void CreditState::reset(){
    ofResetElapsedTimeCounter();
    setFinished(false);
	setNextState("");
}
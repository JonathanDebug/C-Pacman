#include "WinState.h"


WinState::WinState(){
    continueButton = new Button(ofGetWindowWidth()/2-400, ofGetWindowHeight()/2+100, 400, 100, "");
	QuitButton = new Button(ofGetWindowWidth()/2+50, ofGetWindowHeight()/2+100, 400, 100, "");
	this->music.load("music/PacManChampionshipOSTWin.mp3");
	this->Continue.load("images/ContinueButton.png");
	this->Quit.load("images/QuitButton.png");
	this->background.load("images/PacWin4.png");
	background.resize(1024,768);
}

void WinState::tick() {
	if(!music.isPlaying()){
		ofSoundStopAll();
		music.play();
	}
	continueButton->tick();
	if(continueButton->wasPressed()){
		ofSoundStopAll();
		setNextState("PreBoss");
		setFinished(true);

	}
	if(QuitButton->wasPressed()){
		ofSoundStopAll();
		setNextState("over");
		setFinished(true);
		

	}
}
void WinState::render() {
	this->background.draw((ofGetWindowWidth()/2-background.getWidth()/2), (ofGetWindowHeight()/2-background.getHeight()/2)-100);
	ofSetBackgroundColor(0, 0, 0);
	ofDrawBitmapString("Score: " + to_string(score), ofGetWindowWidth()/2-25, ofGetWindowHeight()/2-300, 50);
	ofSetColor(256, 256, 256);
	continueButton->render();
	QuitButton->render();
	ofSetColor(256);
	this->Continue.draw(ofGetWindowWidth()/2-400, ofGetWindowHeight()/2+100, 400, 100);
	this->Quit.draw(ofGetWindowWidth()/2+50, ofGetWindowHeight()/2+100, 400, 100);


}

void WinState::keyPressed(int key){
	
}

void WinState::mousePressed(int x, int y, int button){
	continueButton->mousePressed(x, y);
	QuitButton->mousePressed(x,y);
}

void WinState::reset(){
	setFinished(false);
	setNextState("");
	continueButton->reset();
	QuitButton->reset();
}

void WinState::setScore(int score){
    this->score = score;
}

WinState::~WinState(){
	delete continueButton;
	delete QuitButton;
}
#include "PauseState.h"

// Creates resume and quit buttons.
PauseState::PauseState() {
	this->resume = new Button(ofGetWidth()/2-400, ofGetHeight()/2+100, 400, 100, "");
	this->quit =  new Button(ofGetWidth()/2+50, ofGetHeight()/2+100, 400, 100, "");
	this->music.load("music/PacManChampionshipOSTPause.mp3");
	this->resumeButton.load("images/ResumeButton.png");
	this->quitButton.load("images/QuitButton.png");
	this->background.load("images/background1.jpg");
	this->PauseControls.load("images/PauseControls.png");
}
void PauseState::tick() {
	resume->tick();
	quit->tick();
	if(resume->wasPressed()){
		Paused = true; // Do not mess with this boolean, it is in charge of preventing a gamestate reset after quitting.
		setNextState("Game");
		setFinished(true);

	}
	if(quit->wasPressed()){
		Paused = false; // Do not mess with this boolean, it is in charge of allowing a gamestate reset after quitting.
		setNextState("over");
		setFinished(true);
	}
	if(!music.isPlaying()){
		ofSoundStopAll();
		music.play();
	}
}
// Draws buttons
void PauseState::render() {
	resume->render();
	quit->render();
	ofSetColor(256);
	this->background.draw(ofGetWindowWidth()/2-background.getWidth()/2, ofGetWindowHeight()/2-background.getHeight()/2);
	this->PauseControls.draw(ofGetWindowWidth()/2-PauseControls.getWidth()/2, 0);
	this->resumeButton.draw(ofGetWindowWidth()/2-400, ofGetWindowHeight()/2+100, 400, 100);
	this->quitButton.draw(ofGetWindowWidth()/2+50, ofGetWindowHeight()/2+100, 400, 100);
}

void PauseState::keyPressed(int key){
	
}

void PauseState::mousePressed(int x, int y, int button){
	resume->mousePressed(x,y);
	quit->mousePressed(x,y);
}

PauseState::~PauseState(){

}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	resume->reset();
	quit->reset();
	wasPaused=false;
}
bool PauseState::getPaused(){
	return this->wasPaused;
}
void PauseState::setPaused(bool wasPaused){
	this->wasPaused=wasPaused;
}
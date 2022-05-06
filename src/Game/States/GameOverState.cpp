#include "GameOverState.h"

GameOverState::GameOverState() {
	startButton = new Button(ofGetWindowWidth()/2-150, ofGetWindowHeight()/2+100, 400, 100, " ");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);
	this->music.load("music/PacManChampionshipOSTMenu.mp3");
	this->Start.load("images/startbuttonprototype.png");
	background.load("images/background3.jpg");
	title.load("images/PacPlusPlus.png");

}
void GameOverState::tick() {
	startButton->tick();
	anim->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
	if(!music.isPlaying()){
		ofSoundStopAll();
		music.play();
	}
}
void GameOverState::render() {
	ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, ofGetHeight()/2-300, 50);
	background.draw(ofGetWindowWidth()/2-background.getWidth()/2, ofGetWindowHeight()/2-background.getHeight()/2);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);
	ofSetColor(256);
	this->Start.draw(ofGetWindowWidth()/2-150, ofGetWindowHeight()/2+100, 400, 100);
	title.draw(ofGetWidth()/2-300, ofGetHeight()/2-250, 638, 360);
	startButton->render();
	ofSetColor(256);


}

void GameOverState::keyPressed(int key){
	
}

void GameOverState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void GameOverState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}

void GameOverState::setScore(int sc){
    score = sc;
}

GameOverState::~GameOverState(){
	delete startButton;
	delete anim;
}
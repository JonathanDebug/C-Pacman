#include "MenuState.h"

MenuState::MenuState() {
	startButton = new Button(ofGetWindowWidth()/2-150, ofGetWindowHeight()/2+100, 400, 100, " ");
	img1.load("images/pacman.png");
	Start.load("images/startbuttonprototype.png");
	music.load("music/PacManChampionshipOSTMenu.mp3");
	Title.load("images/PacPlusPlus.png");
	background.load("images/background3.jpg");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void MenuState::tick() {
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
void MenuState::render() {
	ofDrawBitmapString("Pacman Project", ofGetWidth()/2, ofGetHeight()/2-300, 50);
	background.draw(ofGetWindowWidth()/2-background.getWidth()/2, ofGetWindowHeight()/2-background.getHeight()/2);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	Start.draw(ofGetWindowWidth()/2-150, ofGetWindowHeight()/2+100, 400, 100);
	anim->getCurrentFrame().draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);
	startButton->render();
	ofSetColor(256);
	Title.draw(ofGetWidth()/2-300, ofGetHeight()/2-250, 638, 360);


}

void MenuState::keyPressed(int key){
	
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}

MenuState::~MenuState(){
	delete startButton;
	delete anim;
}
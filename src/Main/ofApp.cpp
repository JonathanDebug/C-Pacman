#include "ofApp.h"
#include "Images.h"
#include "PauseState.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0,0,0);
	ofSetFrameRate(30);
	ofSetWindowTitle("Java Game Box");
	loadingImage.load("images/beforemenu.jpg");

}
void ofApp::trueSetup(){
//States
	menuState = new MenuState();
	gameState = new GameState();
	gameOverState = new GameOverState();
	winState = new WinState();
	pauseState = new PauseState();
	bossState = new BossState();
	preState = new PreBossState();
	creditState = new CreditState();
	
	// Initial State
	currentState = menuState;
	//Volume for music
	ofSoundSetVolume(0.5);
	ofResetElapsedTimeCounter();
}

//--------------------------------------------------------------
void ofApp::update(){
	//Apparently, OpenGL, which is what handles the graphics (I think), is not available from frame 1, so we must wait a bit.
	if(ofGetFrameNum() <= 2){
		return;
	}
	if (currentState != nullptr){
		currentState->tick();
		if(currentState->hasFinished()){
			
			if(currentState->getNextState() == "Menu"){
				currentState = menuState;
			}else if(currentState->getNextState() == "Game"){
				currentState = gameState;
			}else if(currentState->getNextState() == "over"){
				gameOverState->setScore(gameState->getFinalScore());
				currentState = gameOverState;
			}else if(currentState->getNextState() == "Win"){
				winState->setScore(gameState->getCurrentScore());
				currentState = winState;	
			}
			else if(currentState->getNextState() == "Pause"){
				currentState = pauseState;
			}else if(currentState->getNextState() == "Boss"){
				currentState = bossState;
			}else if(currentState->getNextState() == "PreBoss"){
				currentState = preState;
			}else if(currentState->getNextState() == "Credits"){
				currentState = creditState;
			}
			currentState->reset();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//These first two ifs are in charge of displaying the loading screen and doing the actual loading. 
	if(ofGetFrameNum() < 2){
		loadingImage.draw(ofGetWidth()/2 - loadingImage.getWidth()/2,ofGetHeight()/2 - loadingImage.getHeight()/2);
		return;
	}
	if(ofGetFrameNum() == 2){
		trueSetup();
		return;
	}
	if(currentState != nullptr){
		currentState->render();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (currentState != nullptr)
		currentState->keyPressed(key);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (currentState != nullptr)
			currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	if (currentState != nullptr)
			currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (currentState != nullptr)
			currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}

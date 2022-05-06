#include "GameState.h"

#include "Entity.h"
#include "PauseState.h"

bool Paused;

GameState::GameState() {
	music.load("music/PacManChampionshipOST1.mp3");
	music2.load("music/PacManChampionshipOST2.mp3");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {
	
	if(!music.isPlaying() && !music2.isPlaying()){
			ofSoundStopAll();
			music.play();
	}
	if(getCurrentScore()>=1000){
		music.stop();
		if(!music2.isPlaying()){
		music2.play();
		}
	}
	map->tick();
	if(map->getPlayer()->getHealth() == 0){
		ofSoundStopAll();
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
		
	}
	if(map->getEmpty() == true){
		ofSoundStopAll();
		setFinished(true);
		setNextState("Win");
		
	}

	
	
}
void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
	if(key == 'y'){
		ofSoundStopAll();
		setFinished(true);
		setNextState("Win");
		
	}

	if(key == 'p'){
		Paused = true;
		ofSoundStopAll();
		setNextState("Pause");
		setFinished(true);
	}

	if(key == 'b'){
		ofSoundStopAll();
		setFinished(true);
		setNextState("PreBoss");
	}
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
	if(!Paused){
	delete map;
	map = MapBuilder().createMap(mapImage);
	}
	Paused = false;
}

int GameState::getFinalScore(){
	return finalScore;
}


GameState::~GameState(){
	delete map;
}





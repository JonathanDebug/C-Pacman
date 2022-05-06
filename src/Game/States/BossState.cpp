#include "BossState.h"
BossState::BossState(){
    this->bossMusic.load("music/BossMusic.mp3");
    ofSoundSetVolume(.4);
    stage.load("images/bossStage.jpg");
    fightButton = new Button(210, 550, 166, 68, "");
    healButton = new Button(470, 550, 166, 68, "");
    magicButton = new Button(370, 550, 166, 68, "");
    superButton = new Button(ofGetWindowWidth()/2+75, 550, 166, 68, "");
    setTurn(true);
}

void BossState::tick(){

    fightButton->tick();
    magicButton->tick();
    healButton->tick();
    superButton->tick();

    if(fightButton->wasPressed() && this->turn == true){ //fighting always deals damage but less than magic
        this->bossHealth-=10;
        ofResetElapsedTimeCounter();
        setTurn(false);
    }
            
    if(magicButton->wasPressed() && this->turn == true){ // magic deals more damaage but has a chance of not hitting the target
        int ran = ofRandom(4);
        ofResetElapsedTimeCounter();
        setTurn(false);
        if(ran % 2 == 0){
            bossHealth-=25;
            superReady+=1;
        }
        else setMissed(true);
    }

    if(healButton->wasPressed() && this->turn == true ){ // 3 default healing potions, can win one if you active super power
        if(this->healpotions > 0  && healingOn == true){
            this->health+=25;
            this->healpotions-=1;
            setHeal(false);
        }
        
    }
    if(superButton->wasPressed() && this->superReady >= 3 && this->turn == true){ // can only be obtained if magic attack hits 3 times or more, it also stacks
        superReady = 0;
        bossHealth -= 50;
        healpotions+=3;
        ofResetElapsedTimeCounter();
        setTurn(false);
        
    } 

    if(this->turn == false){
        int num = ofRandom(4);
        int timer = ofGetElapsedTimef();
        if(timer > 2){bossAtk(num);}
    }

    if(this->health <= 0){
        setFinished(true);
        setNextState("over");
    }

    if(this->bossHealth <= 0){
        setNextState("Credits");
        setFinished(true);
    }


    if(!bossMusic.isPlaying()){
		ofSoundStopAll();
		bossMusic.play();
	}
}


void BossState::bossAtk(int atk){
    setMissed(false);
    switch(atk){

        case 1: this->health -= 10;
                break;
        
        case 2: this->health -= 15;
                break;

        case 3: this->health -= 25;
                break;

        default: this->health -= 5;
                    break;

    }
    setTurn(true);
    setHeal(true);
}

void BossState::render(){
    ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
    this->stage.draw(ofGetWindowWidth()/2-stage.getWidth()/2, ofGetWindowHeight()/2-stage.getHeight()/2);
    ofDrawBitmapString("King Ghost: " + to_string(bossHealth), ofGetWidth()/2-50, ofGetHeight()/2-50, 50);
    ofDrawBitmapString("Health: " + to_string(health), ofGetWidth()/2-50, ofGetHeight()/2+300, 50);
    ofDrawBitmapString("Potions: " + to_string(healpotions), ofGetWindowWidth()/2+10, 600, 50);
    fightButton->render();
    healButton->render();
    magicButton->render();
    superButton->render();
    if(this->turn == false){ofSetColor(256, 0, 0);}
    else if(this->turn == true){ofSetColor(0, 256, 0);}
    ofDrawCircle(ofGetWidth()/2 , ofGetHeight()/2, 10);
    if(this->missed == true){ofDrawBitmapString("You Missed!", ofGetWidth()/2-50, ofGetHeight()/2+100, 50);}
    if(this->superReady >= 3){ofDrawBitmapString("Super Ready", ofGetWindowWidth()/2+125, 600, 50);}
};

void BossState::mousePressed(int x, int y, int button){
	fightButton->mousePressed(x, y);
    healButton->mousePressed(x,y);
    magicButton->mousePressed(x,y);
    superButton->mousePressed(x,y);
}
void BossState::reset(){
	setFinished(false);
	fightButton->reset();
    healButton->reset();
    magicButton->reset();
    superButton->reset();
    this->bossHealth = 300;
    this->health = 150;
    this->healpotions = 3;
    this->superReady = 0;
    setTurn(true);
}

void BossState::keyPressed(int key){
    if(key == 'd'){
        this->bossHealth -=300; //kils boss instantly if you want to see the credits 
    }
}

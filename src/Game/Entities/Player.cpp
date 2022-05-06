#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "PowerUp.h"
#include "PeekABoo.h"
#include "RandomGhost.h"
#include "PeekPower.h"
#include "RandomPowerUp.h"
using namespace std;


Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;
    this->peekRange.setFromCenter(this->x, this->y, 250,250); //init view range, doesnt really matter
    peekCount = 0;
    this->power = new TestPower(false);
    
}
void Player::tick(){
    int lastX = this->x;
    int lastY = this->y;
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
            walkUp->tick();
        }else if(facing == DOWN){
            y+=speed;
            walkDown->tick();
        }else if(facing == LEFT){
            x-=speed;
            walkLeft->tick();
        }else if(facing == RIGHT){
            x+=speed;
            walkRight->tick();
        }
    }

    if(this->getScore()>=1000){
        PeekEnabled = true; //enable peekaboo spawn
    }
    if(this->getScore()>=500 && RanDead == true){
        RandomEnabled = true;
        RanDead = false;
    }

    if(RandomOn){
    bool location = false;
    int random = 0;
    Entity* en;
    while(location == false){
        random = ofRandom(0,em->entities.size());
        en = em->entities.at(random);
        if(dynamic_cast<Dot*>(en)){
            location = true;
        }
    }
    em->entities.erase(em->entities.begin()+random);
    ofRectangle pos = en->getBounds();
    this->x = pos.x;
    this->y = pos.y;
    RandomOn = false;
    }

    //you can change the width and height to make view range bigger or smaller.
    this->peekRange.setFromCenter(this->getBounds().getCenter().x, this->getBounds().getCenter().y, 250, 250); //constanty update the rectangle center so that pac-man view range changes
    for(Entity* entity:em->ghosts){
        PeekABoo* Peek = dynamic_cast<PeekABoo*>(entity); //check if said ghost is a peekaboo ghost
        if(Peek!=nullptr){
            if(this->peekRange.inside(Peek->getBounds())){ //Check if the peek ghost is within pacman view range
                Peek->setinRange(true);
            }
            else{
                Peek->setinRange(false);
            }
        }
    }
    if(PeekMode){
        if(lastX!=this->x){
            peekCount++;
        }
        if(lastY!=this->y){
            peekCount++;
        }
        if(peekCount>=30){
            PeekMode = false;
            peekCount = 0;
        }

    }
}

void Player::render(){
    if(!PeekMode){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());
    if(facing == UP){
        walkUp->getCurrentFrame().draw(x, y, width, height);
        
    }else if(facing == DOWN){
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == LEFT){
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == RIGHT){
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    }
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
    ofSetColor(51,255,51);
    ofDrawBitmapString("Power:" , ofGetWidth()/2-100, 50);
    if(hasPow == true){
        ofDrawCircle(ofGetWidth()/2 + 25 -50, 50, 10);
    }
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            setFacing(UP);
            break;
        case 's':
            setFacing(DOWN);
            break;
        case 'a':
            setFacing(LEFT);
            break;
        case 'd':
            setFacing(RIGHT);
            break;
        case 'n':
            die();
            break;
        case 'm':
        if(health < 3)health++;
        else health = health;
            
            break;
        case ' ':
            hasPow = false;
            if(this->power->getPossess() == true){
            this->power->activate();
            }
            this->power->setPossess(false);
            break;
        case 'c':
            this->em->entities.clear();
            break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

void Player::setFacing(FACING facing){
    this->facing = facing;
}

int Player::getHealth(){
    return health;
}

void Player::setHealth(int h){
    health = h;
}
int Player::getScore(){
    return score;
}

void Player::setScore(int h){
    score = h;
}

void Player::checkCollisions(){
    for(BoundBlock* BoundBlock: em->BoundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=10;
                em->setKillable(true);
            
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            RandomGhost* Random = dynamic_cast<RandomGhost*>(entity);
            if(Random != nullptr){
                this->power = new RandomPowerUp(true);
                hasPow = true;
                RanDead = true;
            }
            PeekABoo* Peek = dynamic_cast<PeekABoo*>(entity);
            if(Peek != nullptr){
                this->power = new PeekPower(true);
                hasPow = true;
            }
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->remove = true;
            }else{
                die();

            }
        }
    }

    
}

void Player::die(){
    if(!PeekMode){
    health--;
    x = spawnX;
    y = spawnY;
    }

}


Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}
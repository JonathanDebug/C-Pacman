#include "PeekABoo.h"

bool PeekEnabled = false;
PeekABoo::PeekABoo(int x, int y, int width, int height, ofImage spritesheet, EntityManager* em, string color) : Ghost(x, y, width, height, spritesheet, em, color) {

}

PeekABoo::~PeekABoo() {
    
}


void PeekABoo::render(){   //this should only draw the peek if hes in the range dictated by the check in pac-man tick()
    if(this->inRange){
        if(getKillable()){
            getKillableAnim()->getCurrentFrame().draw(x,y,width,height);
    }else{
        Entity::render();
    }
    }
}

void PeekABoo::setinRange(bool inRange){
    this->inRange = inRange;
}


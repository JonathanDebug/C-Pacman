#include "RandomGhost.h"

bool RandomEnabled = false;
RandomGhost::RandomGhost(int width, int height, ofImage spritesheet, EntityManager* em, string color, Entity * player): Ghost(x, y, width, height, spritesheet,  em,  color){
    bool location = false;
    int random = 0;
    ofRectangle epos;
    ofRectangle pos = player->getBounds();
    Entity* en;
    while(location == false){
        random = ofRandom(0,em->entities.size());
        en = em->entities.at(random);
        epos = en->getBounds();
        if(dynamic_cast<Dot*>(en) && (pos.x != epos.x && pos.y != epos.y)){
            location = true;
        }
    }
    em->entities.erase(em->entities.begin()+random);
    this->x = epos.x;
    this->y = epos.y;
        
}



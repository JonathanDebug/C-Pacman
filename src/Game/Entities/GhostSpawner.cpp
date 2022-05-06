#include "GhostSpawner.h"
#include "Ghost.h"
#include "PeekABoo.h"
#include "RandomGhost.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(){
    std::vector<string> colors;
    colors.push_back("red");
    colors.push_back("pink");
    colors.push_back("cyan");
    colors.push_back("orange");
    colors.push_back("peek");
    
    if(em->ghosts.size()<4){
        if(spawnCounter == 0){
            spawnGhost(colors[ofRandom(6)]);
            spawnCounter = 30*5;
        }else{
            spawnCounter--;
        }
    }
}
void GhostSpawner::spawnGhost(string color){ //PeekABoo spawns randomly after 1000 points
    if((color=="peek") && (PeekEnabled = true)){
        PeekABoo* Peek = new PeekABoo(x,y,width-2,height-2,sprite,em, color);
        em->ghosts.push_back(Peek);
    }
    
    else{
    Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);
    em->ghosts.push_back(g);
    }
}

void GhostSpawner::spawnRGhost(string color, Entity * player){
    RandomGhost* rg = new RandomGhost(width-2,height-2,sprite,em, color,player);
    em->ghosts.push_back(rg);
}

void GhostSpawner::keyPressed(int key){
    if(key == 'g'){
        int color = ofRandom(5);
        switch(color){
            case 1:
                spawnGhost("red");
                break;
            case 2:
                spawnGhost("pink");
                break;
            case 3:
                spawnGhost("cyan");
                break;
            case 4:
                spawnGhost("orange");
                break;

        }
        
        
    }
    if(key=='l'){
        spawnGhost("peek");
    }

}
    
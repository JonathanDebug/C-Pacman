#pragma once
#include "EntityManager.h"
#include "Animation.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        virtual void render();
        bool getKillable();
        void setKillable(bool);
        EntityManager* getEM();
        Animation* getKillableAnim();
    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=3;
        EntityManager* em;
        Animation* killableAnim;

};
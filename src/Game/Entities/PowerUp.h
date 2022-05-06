#pragma once
#include "Entity.h"

class PowerUp
{
    private:
        bool inPossession;
    public:
        PowerUp();
        PowerUp(bool inPossession);
        virtual ~PowerUp();
        virtual void activate()=0;
        bool getPossess();
        void setPossess(bool inPossession);
};

class TestPower: public PowerUp
{   private:
        bool inPossession;
    public:
        TestPower(){};
        TestPower(bool inPossession);
        ~TestPower(){};
        void activate();
};
#include "PowerUp.h"
#include "Player.h"
using namespace std;


PowerUp::PowerUp(){
}

PowerUp::PowerUp(bool inPossession){
    this->inPossession = inPossession;
}
PowerUp::~PowerUp(){
    cout << "Destructor called." << endl;
}

bool PowerUp::getPossess(){
    return this->inPossession;
}

void PowerUp::setPossess(bool inPossession){
    this->inPossession = inPossession;
}

TestPower::TestPower(bool inPossession){
    this->inPossession = inPossession;
}

void TestPower::activate(){

}
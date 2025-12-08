#include <cmath>
#include "Dust.h"


Dust::Dust(){
    this->color = {0.76, 0.11, 0.11};
    this->radius = 15;
}


void Dust::processDust(Ball& ball){
    this->point = ball.getCenter();
    this->velocity = ball.getVelocity();
}

void Dust::updateLifeTime(const double& timePerTick){
    this->lifetime = this->lifetime - timePerTick;
}
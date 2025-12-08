#pragma once
#include "Color.h"
#include "Point.h"
#include "Velocity.h"
#include "Painter.h"
#include "Ball.hpp"

class Dust: public Ball {
public:
    Dust();
    void processDust(Ball& ball);
    void updateLifeTime(const double& timePerTick);
    bool shouldRemove() const { return lifetime <= 0; }

protected:
    double lifetime = 1.0;
};
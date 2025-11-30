#pragma once
#include "Color.h"
#include "Point.h"
#include "Velocity.h"
#include "Painter.h"
#include "Ball.hpp"

class Dust {
public:
    void processDust(Ball& ball);
    void updateLifeTime(const double& timePerTick);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const ;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    void draw(Painter& painter) const;
    bool shouldRemove() const { return lifetime <= 0; }
private:
    Color color{0.76, 0.11, 0.11};
    Point point;
    Velocity velocity;
    double radius = 15;
    double lifetime = 1.0;
};
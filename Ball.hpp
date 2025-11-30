#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include "Color.h"

class Ball {
public:
    static Ball readFromStream(std::istream& stream);
    void setVelocity(const Velocity& velocity);
    void setCenter(const Point& center);
    bool getIsCollidable();
    Velocity getVelocity() const;
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    void draw(Painter& painter) const;
private:
    Color color;
    Point point;
    Velocity velocity;
    bool isCollidable;
    double radius;
};

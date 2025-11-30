#include <cmath>
#include "Dust.h"


void Dust::processDust(Ball& ball){
    this->point = ball.getCenter();
    this->velocity = ball.getVelocity();
}

void Dust::updateLifeTime(const double& timePerTick){
    this->lifetime = this->lifetime - timePerTick;
}

void Dust::draw(Painter& painter) const {
    painter.draw(point, radius, color);
}

void Dust::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

Velocity Dust::getVelocity() const {
    return this->velocity;
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Dust::setCenter(const Point& center) {
    this->point = center;
}

/**
 * @return центр объекта
 */
Point Dust::getCenter() const {
    return this->point;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Dust::getRadius() const {
    return this->radius;
}
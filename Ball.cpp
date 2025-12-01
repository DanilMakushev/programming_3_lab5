#include "Ball.hpp"
#include <cmath>

// Метод для чтения из потока
Ball Ball::readFromStream(std::istream& stream) {
    Ball ball;
    double vx, vy;
    
    stream >> ball.point >> vx >> vy;
    stream >> ball.color;
    stream >> ball.radius;
    stream >> std::boolalpha >> ball.isCollidable;
    
    Velocity velocity(std::sqrt(vx*vx + vy*vy), std::atan2(vy, vx));
    ball.setVelocity(velocity);
    
    return ball;
}

bool Ball::getIsCollidable(){
    return this->isCollidable;
}
/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */ 
void Ball::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return this->velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(this->getCenter(), this->getRadius(), this->color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    this->point = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return this->point;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return this->radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return M_PI * std::pow(getRadius(), 3) * 4.0 / 3.0;
}
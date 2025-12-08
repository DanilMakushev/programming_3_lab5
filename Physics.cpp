#include "Physics.h"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, const size_t ticks, std::vector<Dust>& dusts) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        move(dusts);
        collideBallsWithBox(balls);
        collideDustsWithBox(dusts);
        collideBalls(balls, dusts);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if ((distanceBetweenCenters2 < collisionDistance2) && (a->getIsCollidable() && b->getIsCollidable())) {
                processCollision(*a, *b, distanceBetweenCenters2);
                Dust dust_a, dust_b;
                dust_a.processDust(*a);
                dust_b.processDust(*b);
                dusts.push_back(dust_a);
                dusts.push_back(dust_b);
            }
        }
    }
}


void Physics::collideDustsWithBox(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        const Point p = dust.getCenter();
        const double r = dust.getRadius();
        Point vector = dust.getVelocity().vector();

        // Обрабатываем каждую стенку: 
        //     если центр шара за допустимыми границами, 
        //     и его скорость (по x или y) не даст ему вернуться обратно, то меняем скорость (по x или y) на противоположную

        // Левая стенка
        if(p.x < topLeft.x + r){
            if(vector.x < 0){
                vector.x = -vector.x;
            }
        }
        // Правая стенка
        if(p.x > bottomRight.x - r){
            if(vector.x > 0){
                vector.x = -vector.x;
            }
        }
        // Верхняя стенка
        if(p.y < topLeft.y + r){
            if(vector.y < 0){ 
                vector.y = -vector.y;
            }
        }
        // Нижняя стенка
        if(p.y > bottomRight.y - r){
            if(vector.y > 0){ 
                vector.y = -vector.y;
            }
        }
        dust.setVelocity(vector);
    }
}


void Physics::collideBallsWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        Point vector = ball.getVelocity().vector();

        // Обрабатываем каждую стенку: 
        //     если центр шара за допустимыми границами, 
        //     и его скорость (по x или y) не даст ему вернуться обратно, то меняем скорость (по x или y) на противоположную

        // Левая стенка
        if(p.x < topLeft.x + r){
            if(vector.x < 0){
                vector.x = -vector.x;
            }
        }
        // Правая стенка
        if(p.x > bottomRight.x - r){
            if(vector.x > 0){
                vector.x = -vector.x;
            }
        }
        // Верхняя стенка
        if(p.y < topLeft.y + r){
            if(vector.y < 0){ 
                vector.y = -vector.y;
            }
        }
        // Нижняя стенка
        if(p.y > bottomRight.y - r){
            if(vector.y > 0){ 
                vector.y = -vector.y;
            }
        }
        ball.setVelocity(vector);
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::move(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        Point newPos =
            dust.getCenter() + dust.getVelocity().vector() * timePerTick * 0.5;
        dust.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}
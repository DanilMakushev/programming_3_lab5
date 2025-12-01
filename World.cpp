#include "World.h"
#include "Painter.h"
#include <fstream>
#include <algorithm>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);

    stream >> topLeft;
    stream >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    Ball ball;
    while (stream.peek(), stream.good()) {
        Ball ball = Ball::readFromStream(stream);
        balls.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    // Вызываем отрисовку каждого эффекта
    for (const Dust& dust : dusts) {
        dust.draw(painter);
    }
}

void World::removeDust(Dust* dust){
    auto it = std::find_if(dusts.begin(), dusts.end(),
        [dust](const Dust& d) { return &d == dust; });
    
    if (it != dusts.end()) {
        dusts.erase(it);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    for (Dust& dust : dusts) {
        dust.updateLifeTime(timePerTick * ticks);
    }

    // Удаляем эффекты с истекшим временем жизни
    for (size_t i = 0; i < dusts.size(); ) {
        if (dusts[i].shouldRemove()) {
            dusts.erase(dusts.begin() + i);
            // Не увеличиваем i, так как элементы сдвинулись
        } else {
            i++;  // Увеличиваем только если не удалили
        }
    }

    physics.update(balls, ticks, dusts);
}
#pragma once
#include "Point.h"
#include <cmath>

class Velocity {
  public:
    inline Velocity() = default;

    /**
     * @brief Конструктор из полярных координат
     * @param abs Абсолютное значение скорости (модуль вектора)
     * @param angle Угол направления скорости в радианах
     * @details Преобразует полярные координаты в декартовы:
     *          x = abs * cos(angle), y = abs * sin(angle)
     */
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        // Создаем вектор направления и умножаем на скорость
        vec = Point{x, y} * abs;
    }

    /**
     * @brief Конструктор из декартовых координат
     * @param vector Вектор скорости в декартовых координатах (x, y)
     */
    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    /**
     * @brief Устанавливает вектор скорости
     * @param vector Новый вектор скорости в декартовых координатах
     */
    inline void setVector(const Point& vector) {
        vec = vector;
    }

    /**
     * @brief Возвращает вектор скорости
     * @return Вектор скорости в декартовых координатах (x, y)
     */
    inline Point vector() const {
        return vec;
    }

  private:
    Point vec; // Внутреннее представление скорости в декартовых координатах
};

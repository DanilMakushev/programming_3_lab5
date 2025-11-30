#include "Color.h"
#include <iostream>

Color::Color() = default;

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}

// Оператора ввода
std::istream& operator>>(std::istream& stream, Color& color) {
    return stream >> color.r >> color.g >> color.b;
}
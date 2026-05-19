#pragma once

#include <cmath>
#include <math.h>

#include <raylib.h>

inline Vector2 operator+(const Vector2& a, const Vector2& b) {
    return {a.x + b.x, a.y + b.y};
}

inline Vector2 RotateVector(const Vector2& vector, float radians) {
    return {vector.x * std::cos(radians) - vector.y * std::sin(radians),
            vector.x * std::sin(radians) + vector.y * std::cos(radians)};
}

inline void DrawCircleExt(const Vector2& vector, float radius, Color color) {
    DrawCircle(vector.x, vector.y, radius, color);
}

inline Rectangle RotateRectangle(const Rectangle& rectangle, double radians) {
    Vector2 vector = RotateVector({rectangle.x, rectangle.y}, radians);
    return Rectangle(vector.x, vector.y, rectangle.width, rectangle.height);
}

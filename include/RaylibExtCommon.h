#pragma once

#include <cmath>
#include <math.h>

#include <raylib.h>
#include <raymath.h>
#include <utility>

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

struct Triangle {
    Vector2 p_1, p_2, p_3;
};

inline Triangle RotateTriangle(const Triangle& triangle, double radians) {
    return {RotateVector(triangle.p_1, radians), RotateVector(triangle.p_2, radians),
            RotateVector(triangle.p_3, radians)};
}

inline Triangle operator+(const Triangle& triangle, const Vector2& vector) {
    return Triangle{triangle.p_1 + vector, triangle.p_2 + vector, triangle.p_3 + vector};
}

inline Triangle operator+(const Vector2& vector, const Triangle& triangle) {
    return triangle + vector;
}

inline Triangle& operator+=(Triangle& triangle, const Vector2& vector) {
    triangle.p_1 = triangle.p_1 + vector;
    triangle.p_2 = triangle.p_2 + vector;
    triangle.p_3 = triangle.p_3 + vector;
    return triangle;
}

inline void DrawTrapezoid(const Triangle& triangle_1, const Triangle& triangle_2,
                          const Vector2& offset) {
    DrawTriangle(triangle_1.p_1 + offset, triangle_1.p_2 + offset, triangle_1.p_3 + offset, BLUE);
    DrawTriangle(triangle_2.p_1 + offset, triangle_2.p_2 + offset, triangle_2.p_3 + offset, BLUE);
}

// side_1 is bottom, side_2 is top side
inline std::pair<Triangle, Triangle> GetTrapezoid(float height, float side_1, float side_2) {
    Vector2 right_botom{side_1 / 2.0f, -height / 2.0f};
    Vector2 right_top{side_2 / 2.0f, height / 2.0f};
    Vector2 left_top{-side_2 / 2.0f, height / 2.0f};
    Vector2 left_bottom{-side_1 / 2.0f, -height / 2.0f};

    return std::make_pair(Triangle{right_botom, left_top, right_top},
                          Triangle{left_bottom, left_top, right_botom});
}

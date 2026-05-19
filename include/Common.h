#pragma once

#include <numbers>

#include "RaylibExtCommon.h"
#include <raylib.h>

struct Vector2D {
    double x, y;
    Vector2D(double x, double y) : x(x), y(y) {}

    Vector2D(const Vector2D& other) = default;

    Vector2D operator+(const Vector2D& other) {
        return Vector2D(this->x + other.x, this->y + other.y);
    }

    Vector2D& operator+=(const Vector2D& other) {
        *this = (*this) + other;
        return *this;
    }

    Vector2D operator+(double scalar) { return Vector2D(this->x + scalar, this->y + scalar); }

    Vector2D operator-(const Vector2D& other) {
        return Vector2D(this->x - other.x, this->y - other.y);
    }

    Vector2D operator-(double scalar) { return (*this) + (-scalar); }

    Vector2D& operator=(const Vector2D& other) = default;

    Vector2D(const Vector2& v) : x(v.x), y(v.y) {}

    explicit operator Vector2() const {
        return Vector2{static_cast<float>(x), static_cast<float>(y)};
    }

    Vector2 ToRaylib() const { return static_cast<Vector2>(*this); }
};

struct Angle {
    double radians;

    Angle(double radians) : radians(radians) {};

    Angle(const Angle& other) = default;

    static Angle FromRadians(double radians) { return Angle{radians}; }

    static Angle FromDegrees(double degrees) {
        double radians = (std::numbers::pi / 180.0) * degrees;
        return Angle{radians};
    }

    inline double GetDegrees() const { return (180.0 / std::numbers::pi) * radians; }

    Angle operator+(const Angle& other) const { return Angle(this->radians + other.radians); }

    Angle& operator+=(const Angle& other) {
        *this = (*this) + other;
        return *this;
    }

    Angle operator-(const Angle& other) const { return Angle(this->radians - other.radians); }

    bool operator==(const Angle& other) const { return this->radians == other.radians; }

    Angle& operator=(const Angle& other) = default;
};

#pragma once

#include <numbers>

#include "RaylibExtCommon.h"
#include <raylib.h>

#define DEBUG

struct Angle {
    double radians;

    Angle(double radians) : radians(radians) {};

    Angle(const Angle& other) = default;

    static Angle FromRadians(double radians) { return Angle{radians}; }

    static Angle FromDegrees(double degrees) {
        double radians = (std::numbers::pi / 180.0) * degrees;
        return Angle{radians};
    }

    inline float GetDegrees() const { return (180.0 / std::numbers::pi) * radians; }

    Angle operator+(const Angle& other) const { return Angle(this->radians + other.radians); }

    Angle& operator+=(const Angle& other) {
        *this = (*this) + other;
        return *this;
    }

    Angle operator-(const Angle& other) const { return Angle(this->radians - other.radians); }

    bool operator==(const Angle& other) const { return this->radians == other.radians; }

    Angle& operator=(const Angle& other) = default;
};

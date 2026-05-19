#pragma once

#include <raylib.h>

#include "Common.h"

struct CarConfig {
    Vector2D start_position;
    Vector2D size;
    Angle start_angle;
    double max_speed;
    Color color;
};

struct PlayerConfig {
    CarConfig car_config;
    unsigned int max_health;
};

inline CarConfig GetDefaultCarConfig() {
    return {{500, 500}, {70, 35}, 0, 200, {85, 166, 80, 255}};
}

inline PlayerConfig GetDefaultPlayerConfig() {
    return {GetDefaultCarConfig(), 100};
}

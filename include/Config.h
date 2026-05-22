#pragma once

#include <raylib.h>

#include "Common.h"

struct CarConfig {
    Vector2 start_position;
    Vector2 size;
    Angle start_angle;
    double max_speed;
    Color color;
};

struct PlayerConfig {
    CarConfig car_config;
    unsigned int max_health;
};

inline CarConfig GetDefaultCarConfig() {
    return {{500, 500}, {70, 35}, 0, 200, {159, 206, 128, 255}};
}

inline PlayerConfig GetDefaultPlayerConfig() {
    return {GetDefaultCarConfig(), 100};
}

struct RoadConfig {
    Vector2 left_top;
    Vector2 right_top;
    Vector2 left_bottom;
    Vector2 right_bottom;
    int number_lanes;
    float sides_thickness;
    int num_separators;
};

inline RoadConfig GetDefaultRoadConfig() {
    return {{0, 300}, {800, 300}, {0, 400}, {800, 400}, 2, 3, 50};
}

struct TreeConfig {
    Vector2 left_top_p;
    Angle rotation;
    float size;
};

inline TreeConfig GetDefaultTreeConfig() {
    return {
        {200, 230},
        1,
        50,
    };
}

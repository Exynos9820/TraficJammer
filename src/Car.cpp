#include "Car.h"
#include "Common.h"
#include "RaylibExtCommon.h"
#include <numbers>
#include <print>
#include <raymath.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <raylib.h>
#include <math.h>
#include <raymath.h>

void Car::Render() {
    const double& radians = angle.radians;
    const float rotation = angle.GetDegrees();
    auto const car_pos = m_position;
    auto const size = m_config.size;
    auto carCentre = size / 2.0f;

    auto recFromV = [](Vector2 pos, Vector2 size) -> Rectangle {
        return {
            .x = pos.x,
            .y = pos.y,
            .width = size.x,
            .height = size.y,
        };
    };

    auto const car_rect = recFromV(car_pos, size);
    DrawRectanglePro(car_rect, carCentre, rotation, m_config.color);

    // Front window
    auto [front_triangle_1, front_triangle_2] =
        GetTrapezoid(0.15f * size.x, 0.7 * size.y, 0.5 * size.y);
    auto front_triangle_offset = Vector2(0, -0.12f * size.x);
    auto front_triangle_1_rotated =
        RotateTriangle(front_triangle_1 + front_triangle_offset, radians + std::numbers::pi / 2);
    auto front_triangle_2_rotated =
        RotateTriangle(front_triangle_2 + front_triangle_offset, radians + std::numbers::pi / 2);
    DrawTrapezoid(front_triangle_1_rotated, front_triangle_2_rotated, car_pos);

    // Back window
    auto [back_triangle_1, back_triangle_2] =
        GetTrapezoid(0.15f * size.x, 0.7 * size.y, 0.5 * size.y);
    auto back_triangle_offset = Vector2(0, -0.28f * size.x);
    auto back_triangle_1_rotated =
        RotateTriangle(back_triangle_1 + back_triangle_offset, radians - std::numbers::pi / 2);
    auto back_triangle_2_rotated =
        RotateTriangle(back_triangle_2 + back_triangle_offset, radians - std::numbers::pi / 2);
    DrawTrapezoid(back_triangle_1_rotated, back_triangle_2_rotated, car_pos);

    // Left window
    auto [left_triangle_1, left_triangle_2] =
        GetTrapezoid(0.13f * size.y, 0.5 * size.x, 0.25 * size.x);
    auto left_triangle_offset = Vector2(-0.06f * size.x, -0.17f * size.x);
    auto left_triangle_1_rotated = RotateTriangle(left_triangle_1 + left_triangle_offset, radians);
    auto left_triangle_2_rotated = RotateTriangle(left_triangle_2 + left_triangle_offset, radians);
    DrawTrapezoid(left_triangle_1_rotated, left_triangle_2_rotated, car_pos);

    // Right window
    auto [right_triangle_1, right_triangle_2] =
        GetTrapezoid(0.13f * size.y, 0.25 * size.x, 0.5 * size.x);
    auto right_triangle_offset = Vector2(-0.06f * size.x, 0.17f * size.x);
    auto right_triangle_1_rotated =
        RotateTriangle(right_triangle_1 + right_triangle_offset, radians);
    auto right_triangle_2_rotated =
        RotateTriangle(right_triangle_2 + right_triangle_offset, radians);
    DrawTrapezoid(right_triangle_1_rotated, right_triangle_2_rotated, car_pos);

    // Number plate
    auto const back_window_offset = Vector2{0.45f, 0.0f} * size;
    auto const back_window_size = Vector2{0.04f, 0.35f} * size;
    auto const back_window_centre = back_window_size / 2.0f;
    auto const back_window_rec = recFromV(car_pos, back_window_size);
    DrawRectanglePro(back_window_rec, back_window_centre - back_window_offset, rotation, WHITE);

    // Lights
    double radius_front = std::min(size.x / 16, size.y / 12);
    double radius_back = std::min(size.x / 20, size.y / 15);

    double partial_width = 9.0 / 20.0 * size.x;
    double partial_height = 3.0 / 8.0 * size.y;

    Vector2 first_light_front = RotateVector(Vector2(partial_width, partial_height), radians);
    Vector2 second_light_front = RotateVector(Vector2(partial_width, -partial_height), radians);
    Vector2 first_light_back = RotateVector(Vector2(-partial_width, partial_height), radians);
    Vector2 second_light_back = RotateVector(Vector2(-partial_width, -partial_height), radians);

    DrawCircleExt(first_light_front + m_position, radius_front, YELLOW);
    DrawCircleExt(second_light_front + m_position, radius_front, YELLOW);
    DrawCircleExt(first_light_back + m_position, radius_back, RED);
    DrawCircleExt(second_light_back + m_position, radius_back, RED);
}

void Car::Render(const Vector2& position) {
    auto& size = m_config.size;
    DrawRectangle(position.x, position.y, size.x, size.y, m_color);
}

void Car::Move(const Vector2& move_vector) {
    this->m_position += move_vector;
}

void Car::Update(const std::chrono::microseconds& ms) {
    // Vector2 direction
    float horizontal_movement = std::cos(angle.radians) * m_current_speed * ms.count() / 1000000;
    float vertical_movement = std::sin(angle.radians) * m_current_speed * ms.count() / 1000000;
    Move({horizontal_movement, vertical_movement});
}

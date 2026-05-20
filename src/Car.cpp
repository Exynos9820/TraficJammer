#include "Car.h"
#include "Common.h"
#include "RaylibExtCommon.h"
#include <raymath.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <raylib.h>
#include <math.h>
#include <raymath.h>

void Car::Render() {
    auto& size = m_config.size;
    const double& radians = angle.radians;
    const float rotation = angle.GetDegrees();

    auto recFromV = [](Vector2 pos, Vector2 size) -> Rectangle {
        return {
            .x = pos.x,
            .y = pos.y,
            .width = size.x,
            .height = size.y,
        };
    };
    auto const carPos = m_position;
    // auto const carPos = Vector2(100.0f, 100.0f);
    auto const carSize = m_config.size;
    auto carCentre = carSize / 2.0f;
    auto const backWindowOffset = Vector2{0.2f, 0.0f} * carSize;
    auto const backWindowSize = Vector2{0.2f, 0.6f} * carSize;
    auto const backWindowCentre = backWindowSize / 2.0f;

    auto const carRect = recFromV(carPos, carSize);
    auto const backWindowRec = recFromV(carPos, backWindowSize);
    DrawRectanglePro(carRect, carCentre, rotation, m_config.color);
    DrawRectanglePro(backWindowRec, backWindowCentre - backWindowOffset, rotation, BLUE);

    // Draw main rectangle

    // Windows
    // Rectangle backWindowRect =
    //     RotateRectangle(Rectangle(m_position.x - 0.3 * size.x, m_position.y - 0.2 * size.y,
    //                               0.2 * size.x, 0.4 * size.y),
    //                     radians);
    Rectangle backWindowRect = Rectangle(0.3 * size.x, 0.2 * size.y, 0.2 * size.x, 0.4 * size.y);
    // Rectangle backWindowRect = Rectangle(-0.3*size.x + m_position.x + size.x/2, 1.0/6.0*size.y +
    // m_position.y + size.y/2, 0.2*size.x, 0.4 * size.y); Rectangle a =
    // RotateRectangle(Rectangle(m_position.x - 0.3 * size.x, m_position.y - 0.2 * size.y,  0.2 *
    // size.x, 0.4 * size.y), radians);
    // Vector2 origin_back_rect = {
    //     .x = (float)m_position.x + origin.x,
    //     .y = (float)m_position.y + origin.y,
    // };
    // // DrawRectangleRec(backWindowRect, BLUE);
    // DrawRectanglePro(backWindowRect, origin_back_rect, rotation, BLUE);

    // Lights
    double radius_front = std::min(size.x / 12, size.y / 8);
    double radius_back = std::min(size.x / 16, size.y / 10);

    double partial_width = 9.0 / 20.0 * size.x;
    double partial_height = 3.0 / 8.0 * size.y;

    Vector2 first_light_front = RotateVector(Vector2(partial_width, partial_height), radians);
    Vector2 second_light_front = RotateVector(Vector2(partial_width, -partial_height), radians);
    Vector2 first_light_back = RotateVector(Vector2(-partial_width, partial_height), radians);
    Vector2 second_light_back = RotateVector(Vector2(-partial_width, -partial_height), radians);

    DrawCircleExt(first_light_front + static_cast<Vector2>(m_position), radius_front, YELLOW);
    DrawCircleExt(second_light_front + static_cast<Vector2>(m_position), radius_front, YELLOW);
    DrawCircleExt(first_light_back + static_cast<Vector2>(m_position), radius_back, RED);
    DrawCircleExt(second_light_back + static_cast<Vector2>(m_position), radius_back, RED);
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

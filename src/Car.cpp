#include "Car.h"
#include "Common.h"
#include "RaylibExtCommon.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <raylib.h>
#include <math.h>

void Car::Render() {
    auto& size = m_config.size;
    const double& radians = angle.radians;
    const float rotation = angle.GetDegrees();

    Rectangle carRect = Rectangle(m_position.x, m_position.y, size.x, size.y);
    // Center of the car
    Vector2 origin = Vector2(size.x / 2.0f, size.y / 2.0f);

    // Draw main rectangle
    DrawRectanglePro(carRect, origin, rotation, m_color);

    // Windows
    Rectangle backWindowRect =
        RotateRectangle(Rectangle(m_position.x - 0.3 * size.x, m_position.y - 0.2 * size.y,
                                  0.2 * size.x, 0.4 * size.y),
                        radians);
    // Rectangle backWindowRect = Rectangle(-0.3*size.x + m_position.x + size.x/2, 1.0/6.0*size.y +
    // m_position.y + size.y/2, 0.2*size.x, 0.4 * size.y); Rectangle a =
    // RotateRectangle(Rectangle(m_position.x - 0.3 * size.x, m_position.y - 0.2 * size.y,  0.2 *
    // size.x, 0.4 * size.y), radians);
    Vector2 origin_back_rect = Vector2(size.x * 0.3, 0);
    // DrawRectangleRec(backWindowRect, BLUE);
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

void Car::Render(const Vector2D& position) {
    auto& size = m_config.size;
    DrawRectangle(position.x, position.y, size.x, size.y, m_color);
}

void Car::Move(const Vector2D& move_vector) {
    this->m_position += move_vector;
}

void Car::Update(const std::chrono::microseconds& ms) {
    // Vector2D direction
    double horizontal_movement = std::cos(angle.radians) * m_current_speed * ms.count() / 1000000;
    double vertical_movement = std::sin(angle.radians) * m_current_speed * ms.count() / 1000000;
    Move({horizontal_movement, vertical_movement});
}

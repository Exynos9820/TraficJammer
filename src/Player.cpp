#include <cerrno>
#include <raylib.h>

#include "Player.h"
#include "Common.h"

void Player::Update(const std::chrono::microseconds& ms) {
    double max_speed = m_config.car_config.max_speed;
    if (IsKeyDown(KEY_W)) {
        m_car.m_current_speed += (max_speed - m_car.m_current_speed) * ms.count() / 100000;
        m_car.m_current_speed = std::min(m_car.m_current_speed, max_speed);
    }
    if (IsKeyDown(KEY_S)) {
        m_car.m_current_speed -= std::abs(max_speed - m_car.m_current_speed) * ms.count() / 100000;
        m_car.m_current_speed = std::max(m_car.m_current_speed, -max_speed);
    }

    if (IsKeyDown(KEY_SPACE)) {
        m_car.m_current_speed -= std::abs(max_speed - m_car.m_current_speed) * ms.count() / 100000;
        m_car.m_current_speed = std::max(m_car.m_current_speed, 0.0);
    }

    if (IsKeyDown(KEY_A)) {
        m_car.angle.radians -= 0.3 * ms.count() / 100000;
    }

    if (IsKeyDown(KEY_D)) {
        m_car.angle.radians += 0.3 * ms.count() / 100000;
    }
    m_car.Update(ms);
}

void Player::Move(const Vector2D& move_vector) {
    m_car.Move(move_vector);
}

void Player::Render() {
    m_car.Render();
}

void Player::Render(const Vector2D& position) {}

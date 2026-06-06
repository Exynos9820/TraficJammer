#include <cerrno>
#include <cstdlib>
#include <raylib.h>

#include "Player.h"
#include "Car.h"
#include "Common.h"

void Player::Update(const std::chrono::microseconds& ms) {
    // TODO(exynos9820) Some clever system for speed?
    const double& max_speed = m_config.car_config.max_speed;
    double& current_speed = m_car.m_current_speed;
    if (IsKeyDown(KEY_W)) {
        if (current_speed >= 0) {
            current_speed += 10.0 * ms.count() / 100000;
        } else {
            current_speed += 30.0 * ms.count() / 100000;
        }
        current_speed = std::min(current_speed, max_speed);
    }
    if (IsKeyDown(KEY_S)) {
        if (current_speed >= 0) {
            current_speed -= 30.0 * ms.count() / 100000;
        } else {
            current_speed -= 10.0 * ms.count() / 100000;
        }
        current_speed = std::max(current_speed, -max_speed);
    }

    if (IsKeyDown(KEY_SPACE)) {
        if (current_speed >= 0) {
            current_speed -= 30.0 * ms.count() / 100000;
            current_speed = std::max(current_speed, 0.0);
        } else {
            current_speed += 30.0 * ms.count() / 100000;
            current_speed = std::min(current_speed, 0.0);
        }
    }

    if (IsKeyDown(KEY_A) and m_car.m_current_speed != 0) {
        m_car.angle.radians -=
            0.3 * ms.count() * std::min(std::abs(current_speed * 2 / max_speed), 1.0) / 100000;
    }

    if (IsKeyDown(KEY_D) and m_car.m_current_speed != 0) {
        m_car.angle.radians += 0.3 * ms.count() / 100000;
    }
}

void Player::Render() {
    m_car.Render();
}

const Collider Player::GetCollider() {
    return m_car.GetCollider();
}

const Vector2 Player::GetMoveVector(const std::chrono::microseconds& ms) {
    const auto& angle = this->m_car.angle;
    const auto& speed = this->m_car.m_current_speed;
    float horizontal_movement = std::cos(angle.radians) * speed * ms.count() / 1000000 + delta.x;
    float vertical_movement = std::sin(angle.radians) * speed * ms.count() / 1000000 + delta.y;
    delta = {0, 0};
    return {-horizontal_movement, -vertical_movement};
}

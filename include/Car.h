#pragma once

#include "Common.h"
#include "Config.h"
#include "Drawable.h"
#include <raylib.h>

class Car : public Drawable {
  private:
    CarConfig m_config;
    Vector2 m_position;
    Angle angle;
    Color m_color;
    double m_current_speed = 2;

  public:
    Car(const CarConfig& config)
        : m_position(config.start_position), m_color(config.color), angle(config.start_angle),
          m_config(config) {}

    void Render() override;
    void Render(const Vector2& position) override;
    void Move(const Vector2& move_vector) override;
    void Update(const std::chrono::microseconds& ms) override;

    friend class Player;
};

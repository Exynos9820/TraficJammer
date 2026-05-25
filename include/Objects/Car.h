#pragma once

#include "Common.h"
#include "Config.h"
#include "Object.h"

class Car : public Object {
  private:
    CarConfig m_config;
    Angle angle;
    Color m_color;
    double m_current_speed = 2;

  public:
    Car(const CarConfig& config)
        : Object(config.start_position), m_color(config.color), angle(config.start_angle),
          m_config(config) {}

    void Render() override;
    void Render(const Vector2& position) override;
    void Update(const std::chrono::microseconds& ms) override;

    friend class Player;
};

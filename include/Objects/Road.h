#pragma once

#include "Config.h"
#include "Object.h"

class Road : public Object {
  private:
    RoadConfig m_config;

  public:
    Road(const RoadConfig& config) : m_config(config) {}
    void Render() override;
    void Render(const Vector2& position) override;
    void Move(const Vector2& move_vector) override;
    void Update(const std::chrono::microseconds& ms) override;
};

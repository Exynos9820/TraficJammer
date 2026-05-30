#pragma once

#include "Config.h"
#include "Object.h"

class Road : public Object {
  private:
    RoadConfig m_config;

  public:
    Road(const RoadConfig& config) : Object(config.start_left_top), m_config(config) {}
    void Render() override;
    void Update(const std::chrono::microseconds& ms) override;
    const Collider GetCollider() override;
};

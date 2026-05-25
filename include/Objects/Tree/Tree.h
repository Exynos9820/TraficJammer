#pragma once

#include "Config.h"
#include "Object.h"

class Tree : public Object {
  protected:
    TreeConfig m_config;

  public:
    Tree(const TreeConfig& config) : m_config(config) {}
    void Render(const Vector2& position) override;
    void Move(const Vector2& move_vector) override;
    void Update(const std::chrono::microseconds& ms) override;
};

#pragma once

#include "Config.h"
#include "Object.h"
#include <raylib.h>

class Tree : public Object {
  protected:
    TreeConfig m_config;

  public:
    Tree(const TreeConfig& config) : Object(config.start_left_top_p), m_config(config) {}
    void Render(const Vector2& position) override;
    void Update(const std::chrono::microseconds& ms) override;
};

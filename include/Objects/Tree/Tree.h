#pragma once

#include "Collision.h"
#include "Config.h"
#include "Object.h"
#include <raylib.h>

class Tree : public Object {
  protected:
    TreeConfig m_config;

  public:
    Tree(const TreeConfig& config) : Object(config.start_left_top_p), m_config(config) {
        m_collider_type = ColliderType::STATIC;
    }
    void Update(const std::chrono::microseconds& ms) override;
    virtual const Collider GetCollider() override;
};

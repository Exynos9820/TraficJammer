#pragma once

#include "Collision.h"
#include <chrono>

#include <Common.h>

class Object {
  protected:
    Vector2 m_position;
    ColliderType m_collider_type;

  public:
    Object(Vector2 position) : m_position(position), m_collider_type(ColliderType::TRIGGER) {}
    virtual void Update(const std::chrono::microseconds& ms) = 0;
    virtual void Render() = 0;
    virtual const Collider GetCollider() = 0;
    virtual void Stop() {};
    virtual const ColliderType& GetColliderType() { return m_collider_type; }
    virtual void Move(const Vector2& move_vector) { m_position += move_vector; }
};

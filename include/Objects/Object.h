#pragma once

#include <chrono>

#include <Common.h>

class Object {
  protected:
    Vector2 m_position;

  public:
    Object(Vector2 position) : m_position(position) {}
    virtual void Update(const std::chrono::microseconds& ms) = 0;
    virtual void Render() = 0;
    virtual void Render(const Vector2& position) = 0;
    void Move(const Vector2& move_vector) { m_position += move_vector; }
};

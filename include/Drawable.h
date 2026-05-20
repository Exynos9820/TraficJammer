#pragma once

#include "Common.h"
#include <chrono>

class Drawable {
  public:
    virtual void Move(const Vector2& move_vector) = 0;
    virtual void Update(const std::chrono::microseconds& ms) = 0;
    virtual void Render() = 0;
    virtual void Render(const Vector2& position) = 0;
};

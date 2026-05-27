/*********************************************************************
 * @file  Collision.h
 *
 * @brief Colliders definitions and helper functions.
 *
 * Colliders are always created in-place
 *********************************************************************/
#pragma once

#include <variant>

#include <raylib.h>

/**
 * @brief Circle collider
 *
 * Simpliest possible collider that is used for some round objects
 * like trees or etc.
 */
struct CircleCollider {
    Vector2 position;
    float radius;
};

/**
 * @brief Rectangle collider with rotation
 *
 * Simple rectangle collider that is used, for example for cars
 * As a position Rectanle always takes the left top corner of rectangle,
 * to maintain compability with raylib
 */
struct RectangleCollider {
    Rectangle rec;
    float rotation;
};

struct CollisionManifold {
    Vector2 normal;
    float depth;
};

using Collider = std::variant<CircleCollider, RectangleCollider>;

bool CollisionTriggered(const Collider& c1, const Collider& c2);

const CollisionManifold CheckCollision(const Collider& c1, const Collider& c2);

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
 * @brief Three main types of colliders
 *
 * KINEMATIC - can be moved by other object
 * Example: Car
 *
 * STATIC - has a collider and interacts with others, but unmovable
 * Example: Tree, House
 *
 * TRIGGER - used for detection and triggering some events
 * Example: Check if car is on the road
 *
 */
enum ColliderType {
    KINEMATIC,
    STATIC,
    TRIGGER,
};

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

const CollisionManifold GetCollisionManifold(const Collider& c1, const Collider& c2);

const void DrawCollider(const Collider& c);

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <raylib.h>
#include <variant>

#include "Collision.h"
#include "RaylibExtCommon.h"
#include <raymath.h>

auto min_x_from_rec = [](RotatedRectangle rec) -> float {
    return std::min(std::min(rec.p1.x, rec.p2.x), std::min(rec.p3.x, rec.p4.x));
};

auto min_y_from_rec = [](RotatedRectangle rec) -> float {
    return std::min(std::min(rec.p1.y, rec.p2.y), std::min(rec.p3.y, rec.p4.y));
};

auto max_x_from_rec = [](RotatedRectangle rec) -> float {
    return std::max(std::max(rec.p1.x, rec.p2.x), std::max(rec.p3.x, rec.p4.x));
};

auto max_y_from_rec = [](RotatedRectangle rec) -> float {
    return std::max(std::max(rec.p1.y, rec.p2.y), std::max(rec.p3.y, rec.p4.y));
};

auto check_intersection = [](float min_p1, float max_p1, float min_p2, float max_p2) -> bool {
    return (min_p2 > min_p1 and min_p2 < max_p1) or (max_p2 > min_p1 and max_p2 < max_p1);
};

/**
 * @brief Handles a detection if two circle colliders have coliision
 *
 * @param c1 circle collider
 * @param c2 circle collider
 *
 * @return boolean
 */
bool CollisionTriggered(const CircleCollider& c1, const CircleCollider& c2) {
    Vector2 distance_vec = c1.position - c2.position;
    float distance = distance_vec.x * distance_vec.x + distance_vec.y * distance_vec.y;
    return distance < (c1.radius + c2.radius) * (c1.radius + c2.radius);
}

/**
 * @brief Handles a detection if rectangle and circle collided
 *
 * @param c1 circle collider
 * @param c2 rectangle collider
 *
 * @return boolean
 */
bool CollisionTriggered(const CircleCollider& c1, const RectangleCollider& c2) {
    // We need to find rectangle projection on X axis
    // If we do it for both of them and then check if there is any intersection
    // No intersection means that they don't intersect at all
    RotatedRectangle rec2 = RotateRectangle(c2.rec, c2.rotation);
    Vector2 corners2[4] = {rec2.p1, rec2.p2, rec2.p3, rec2.p4};

    auto edge_normal = [](Vector2 a, Vector2 b) -> Vector2 {
        // edge vector
        Vector2 edge = b - a;
        float len = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        return {-edge.y / len, edge.x / len};
    };
    // We need 4 axes for projection
    Vector2 axes[2] = {
        edge_normal(rec2.p1, rec2.p2),
        edge_normal(rec2.p2, rec2.p3),
    };

    for (const auto& axis : axes) {
        // we now need to project  everything on this vector
        float center_proj = Vector2DotProduct(c1.position, axis);
        float min1 = center_proj - c1.radius;
        float max1 = center_proj + c1.radius;

        float min2 = -FLT_MAX;
        float max2 = FLT_MAX;
        for (const auto corner : corners2) {
            float product = Vector2DotProduct(corner, axis);
            min2 = (product < min2) ? product : min2;
            max2 = (product > max2) ? product : max2;
        }

        // if there is no intersection on at least one axis - so no intersection at all
        if (!check_intersection(min1, max1, min2, max2))
            return false;
    }

    // if we did got intersection on each axis -> so there is an intersection
    return true;
}

/**
 * @brief Handles a detection if rectangle and circle collided
 *
 * @param c1 rectangle collider
 * @param c2 circle collider
 *
 * @return boolean
 */
bool CollisionTriggered(const RectangleCollider& c1, const CircleCollider& c2) {
    return CollisionTriggered(c2, c1);
}

/**
 * @brief Handles a detection if two rectangles collided
 *
 * @param c1 rectangle collider
 * @param c2 rectangle collider
 *
 * @return boolean
 */
bool CollisionTriggered(const RectangleCollider& c1, const RectangleCollider& c2) {
    // We need to find rectangle projection on X axis
    // If we do it for both of them and then check if there is any intersection
    // No intersection means that they don't intersect at all
    RotatedRectangle rec1 = RotateRectangle(c1.rec, c1.rotation);
    RotatedRectangle rec2 = RotateRectangle(c2.rec, c2.rotation);
    Vector2 corners1[4] = {rec1.p1, rec1.p2, rec1.p3, rec1.p4};
    Vector2 corners2[4] = {rec2.p1, rec2.p2, rec2.p3, rec2.p4};

    auto edge_normal = [](Vector2 a, Vector2 b) -> Vector2 {
        // edge vector
        Vector2 edge = b - a;
        float len = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        return {-edge.y / len, edge.x / len};
    };
    // We need 4 axes for projection
    Vector2 axes[4] = {
        edge_normal(rec1.p1, rec1.p2),
        edge_normal(rec1.p2, rec1.p3),
        edge_normal(rec2.p1, rec2.p2),
        edge_normal(rec2.p2, rec2.p3),
    };

    for (const auto& axis : axes) {
        // we now need to project  everything on this vector
        float min1 = FLT_MAX;
        float max1 = -FLT_MAX;
        for (const auto corner : corners1) {
            float product = Vector2DotProduct(corner, axis);
            min1 = (product < min1) ? product : min1;
            max1 = (product > max1) ? product : max1;
        }

        float min2 = -FLT_MAX;
        float max2 = FLT_MAX;
        for (const auto corner : corners2) {
            float product = Vector2DotProduct(corner, axis);
            min2 = (product < min2) ? product : min2;
            max2 = (product > max2) ? product : max2;
        }

        // if there is no intersection on at least one axis - so no intersection at all
        if (!check_intersection(min1, max1, min2, max2))
            return false;
    }

    // if we did got intersection on each axis -> so there is an intersection
    return true;
}

bool CollisionTriggered(const Collider& c1, const Collider& c2) {
    return std::visit([](auto const& a, auto const& b) { return CollisionTriggered(a, b); }, c1,
                      c2);
}

/**
 * @brief Calculted a manifold between two circles
 *
 * @param c1 circle collider
 * @param c2 circle collider
 *
 * @return CollisionManifold that consists from normal and depth
 */
CollisionManifold GetCollisionManifold(const CircleCollider& c1, const CircleCollider& c2) {
    Vector2 diff = c2.position - c1.position;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float depth = c1.radius + c2.radius - dist;
    Vector2 normal = diff / dist;
    return {normal, depth};
}

/**
 * @brief Calculted a manifold between two rectangles
 *
 * @param c1 rectangle collider
 * @param c2 rectangle collider
 *
 * @return CollisionManifold that consists from normal and depth
 */
CollisionManifold GetCollisionManifold(const RectangleCollider& c1, const RectangleCollider& c2) {
    // We need to find rectangle projection on X axis
    // If we do it for both of them and then check if there is any intersection
    // No intersection means that they don't intersect at all
    RotatedRectangle rec1 = RotateRectangle(c1.rec, c1.rotation);
    RotatedRectangle rec2 = RotateRectangle(c2.rec, c2.rotation);
    Vector2 corners1[4] = {rec1.p1, rec1.p2, rec1.p3, rec1.p4};
    Vector2 corners2[4] = {rec2.p1, rec2.p2, rec2.p3, rec2.p4};

    float depth = 0;
    Vector2 diff = (rec1.p1 + rec1.p3) / 2.0f - (rec2.p1 + rec2.p3) / 2.0f;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    Vector2 normal = diff / dist;

    auto edge_normal = [](Vector2 a, Vector2 b) -> Vector2 {
        // edge vector
        Vector2 edge = b - a;
        float len = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        return {-edge.y / len, edge.x / len};
    };
    // We need 4 axes for projection
    Vector2 axes[4] = {
        edge_normal(rec1.p1, rec1.p2),
        edge_normal(rec1.p2, rec1.p3),
        edge_normal(rec2.p1, rec2.p2),
        edge_normal(rec2.p2, rec2.p3),
    };

    for (const auto& axis : axes) {
        // we now need to project  everything on this vector
        float min1 = FLT_MAX;
        float max1 = -FLT_MAX;
        for (const auto corner : corners1) {
            float product = Vector2DotProduct(corner, axis);
            min1 = (product < min1) ? product : min1;
            max1 = (product > max1) ? product : max1;
        }

        float min2 = -FLT_MAX;
        float max2 = FLT_MAX;
        for (const auto corner : corners2) {
            float product = Vector2DotProduct(corner, axis);
            min2 = (product < min2) ? product : min2;
            max2 = (product > max2) ? product : max2;
        }

        if (!check_intersection(min1, max1, min2, max2))
            depth = std::min(max1, max2) - std::max(min1, min2);
    }

    // if we did got intersection on each axis -> so there is an intersection
    return {{normal}, depth};
}

/**
 * @brief Calculted a manifold between circle and rectangle
 *
 * @param c1 circle collider
 * @param c2 rectangle collider
 *
 * @return CollisionManifold that consists from normal and depth
 */
CollisionManifold GetCollisionManifold(const RectangleCollider& c2, const CircleCollider& c1) {
    RotatedRectangle rec2 = RotateRectangle(c2.rec, c2.rotation);
    Vector2 corners2[4] = {rec2.p1, rec2.p2, rec2.p3, rec2.p4};

    auto edge_normal = [](Vector2 a, Vector2 b) -> Vector2 {
        // edge vector
        Vector2 edge = b - a;
        float len = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        return {-edge.y / len, edge.x / len};
    };
    // We need 4 axes for projection
    Vector2 axes[2] = {
        edge_normal(rec2.p1, rec2.p2),
        edge_normal(rec2.p2, rec2.p3),
    };

    float depth = 0;
    Vector2 diff = c1.position - (rec2.p1 + rec2.p3) / 2.0f;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    Vector2 normal = diff / dist;

    for (const auto& axis : axes) {
        // we now need to project  everything on this vector
        float center_proj = Vector2DotProduct(c1.position, axis);
        float min1 = center_proj - c1.radius;
        float max1 = center_proj + c1.radius;

        float min2 = -FLT_MAX;
        float max2 = FLT_MAX;
        for (const auto corner : corners2) {
            float product = Vector2DotProduct(corner, axis);
            min2 = (product < min2) ? product : min2;
            max2 = (product > max2) ? product : max2;
        }

        // if there is no intersection on at least one axis - so no intersection at all
        if (!check_intersection(min1, max1, min2, max2))
            depth = std::min(max1, max2) - std::max(min1, min2);
    }
    return {{normal}, depth};
}

/**
 * @brief Calculted a manifold between circle and rectangle
 *
 * @param c1 circle collider
 * @param c2 rectangle collider
 *
 * @return CollisionManifold that consists from normal and depth
 */
CollisionManifold GetCollisionManifold(const CircleCollider& c1, const RectangleCollider& c2) {
    RotatedRectangle rec2 = RotateRectangle(c2.rec, c2.rotation);
    Vector2 corners2[4] = {rec2.p1, rec2.p2, rec2.p3, rec2.p4};

    auto edge_normal = [](Vector2 a, Vector2 b) -> Vector2 {
        // edge vector
        Vector2 edge = b - a;
        float len = std::sqrt(edge.x * edge.x + edge.y * edge.y);
        return {-edge.y / len, edge.x / len};
    };
    // We need 4 axes for projection
    Vector2 axes[2] = {
        edge_normal(rec2.p1, rec2.p2),
        edge_normal(rec2.p2, rec2.p3),
    };

    float depth = 0;
    Vector2 diff = c1.position - (rec2.p1 + rec2.p3) / 2.0f;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    Vector2 normal = diff / dist;

    for (const auto& axis : axes) {
        // we now need to project  everything on this vector
        float center_proj = Vector2DotProduct(c1.position, axis);
        float min1 = center_proj - c1.radius;
        float max1 = center_proj + c1.radius;

        float min2 = -FLT_MAX;
        float max2 = FLT_MAX;
        for (const auto corner : corners2) {
            float product = Vector2DotProduct(corner, axis);
            min2 = (product < min2) ? product : min2;
            max2 = (product > max2) ? product : max2;
        }

        // if there is no intersection on at least one axis - so no intersection at all
        if (!check_intersection(min1, max1, min2, max2))
            depth = std::min(max1, max2) - std::max(min1, min2);
    }
    return {{normal}, depth};
}

/**
 * @brief Calculted a manifold between two colliders
 *
 * @param c1 circle collider
 * @param c2 rectangle collider
 *
 * @return CollisionManifold that consists from normal and depth
 */
CollisionManifold GetCollisionManifold(const Collider& c1, const Collider& c2) {
    return std::visit([](auto const& a, auto const& b) { return GetCollisionManifold(a, b); }, c1,
                      c2);
}

/**
 * @brief Handles a detection if two colliders of any shape collided
 *
 * @param c1 first collider
 * @param c2 second collider
 *
 * @return boolean
 */
const CollisionManifold CheckCollision(const Collider& c1, const Collider& c2) {
    if (!CollisionTriggered(c1, c2)) {
        // if no trigger - return empty Collision manifold
        return {{0, 0}, 0};
    }

    // if there is a collision, now we can calculate manifold

    return GetCollisionManifold(c1, c2);
}

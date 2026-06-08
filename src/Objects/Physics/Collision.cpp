/*********************************************************************
 * @file  Collision.cpp
 *
 * @brief Implementations of functions for collision
 *
 * Colliders are always created in-place
 *********************************************************************/

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <raylib.h>
#include <variant>

#include "Collision.h"
#include "RaylibExtCommon.h"
#include <raymath.h>

/**
 * @brief Checks if there is any intersection between points
 *
 */
auto check_intersection = [](float min_p1, float max_p1, float min_p2, float max_p2) -> bool {
    return (min_p2 > min_p1 and min_p2 < max_p1) or (max_p2 > min_p1 and max_p2 < max_p1) or
           (min_p2 < min_p1 and max_p2 > max_p1);
};

auto edge_normal = [](Vector2 a, Vector2 b) -> Vector2 {
    // edge vector
    Vector2 edge = b - a;
    float len = std::sqrt(edge.x * edge.x + edge.y * edge.y);
    return {-edge.y / len, edge.x / len};
};

/**
 * @brief Calculted a manifold between two circles
 *
 * @param c1 circle collider
 * @param c2 circle collider
 *
 * @return CollisionManifold that consists from normal and depth
 *
 * Normal - just vector between two circle centers
 * Depth - how "deep" are rectangles in each other
 */
CollisionManifold GetCollisionManifold(const CircleCollider& c1, const CircleCollider& c2) {
    Vector2 diff = c2.position - c1.position;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float depth = c1.radius + c2.radius - dist;
    Vector2 normal = diff / dist;
    return {normal, depth};
}

/**
 * @brief Calculate a manifold between two rectangles
 *
 * @param c1 rectangle collider
 * @param c2 rectangle collider
 *
 * @return CollisionManifold that consists from normal and depth
 *
 * Normal - distance between rectangles centers
 * Depth - max length of intersection of projections on axes
 * To check it we need to project on 4 axes, normales of rectangles
 * Basically all directions of rectangles sides
 */
CollisionManifold GetCollisionManifold(const RectangleCollider& c1, const RectangleCollider& c2) {
    // We need to find rectangle projection on X axis
    // If we do it for both of them and then check if there is any intersection
    // No intersection means that they don't intersect at all
    RotatedRectangle rec1 = RotateRectangle(c1.rec, c1.rotation);
    RotatedRectangle rec2 = RotateRectangle(c2.rec, c2.rotation);
    Vector2 corners1[4] = {rec1.p1, rec1.p2, rec1.p3, rec1.p4};
    Vector2 corners2[4] = {rec2.p1, rec2.p2, rec2.p3, rec2.p4};

    float depth = FLT_MAX;
    Vector2 diff = (rec1.p1 + rec1.p3) / 2.0f - (rec2.p1 + rec2.p3) / 2.0f;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    Vector2 normal = diff / dist;

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

        float min2 = FLT_MAX;
        float max2 = -FLT_MAX;
        for (const auto corner : corners2) {
            float product = Vector2DotProduct(corner, axis);
            min2 = (product < min2) ? product : min2;
            max2 = (product > max2) ? product : max2;
        }

        if (!check_intersection(min1, max1, min2, max2))
            return {0, 0, 0};

        float curr_depth = std::min(max1, max2) - std::max(min1, min2);
        if (curr_depth < depth) {
            depth = curr_depth;
            normal = axis;
        }
    }

    // if we did got intersection on each axis -> so there is an intersection
    return {{normal}, depth};
}

/**
 * @brief Calculate a manifold between circle and rectangle
 *
 * @param c1 circle collider
 * @param c2 rectangle collider
 *
 * @return CollisionManifold that consists from normal and depth
 */
CollisionManifold GetCollisionManifold(const RectangleCollider& c1, const CircleCollider& c2) {
    auto manifold = GetCollisionManifold(c2, c1);
    return {{-manifold.normal.x, -manifold.normal.y}, manifold.depth};
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

    Vector2 closest_corner = rec2.p1;
    float min_dist = FLT_MAX;
    // find closest corner to the circle center
    for (auto& corner : corners2) {
        Vector2 diff = c1.position - corner;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (dist < min_dist) {
            closest_corner = corner;
            min_dist = dist;
        }
    }

    Vector2 corner_diff = c1.position - closest_corner;
    float corner_len = std::sqrt(corner_diff.x * corner_diff.x + corner_diff.y * corner_diff.y);
    Vector2 corner_axis = (corner_len > 0) ? corner_diff / corner_len : Vector2{1.0f, 0.0f};

    // We need 4 axes for projection
    Vector2 axes[3] = {edge_normal(rec2.p1, rec2.p2), edge_normal(rec2.p2, rec2.p3), corner_axis};

    float depth = FLT_MAX;
    Vector2 diff = c1.position - (rec2.p1 + rec2.p3) / 2.0f;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    Vector2 normal = diff / dist;

    for (const auto& axis : axes) {
        // we now need to project  everything on this vector
        float center_proj = Vector2DotProduct(c1.position, axis);
        float min1 = center_proj - c1.radius;
        float max1 = center_proj + c1.radius;

        float min2 = FLT_MAX;
        float max2 = -FLT_MAX;
        for (const auto corner : corners2) {
            float product = Vector2DotProduct(corner, axis);
            min2 = (product < min2) ? product : min2;
            max2 = (product > max2) ? product : max2;
        }

        if (!check_intersection(min1, max1, min2, max2))
            return {{0, 0}, 0};

        float curr_depth = std::min(max1, max2) - std::max(min1, min2);
        if (curr_depth < depth) {
            depth = curr_depth;
            normal = axis;
        }
    }

    Vector2 rect_center = (rec2.p1 + rec2.p3) / 2.0f;
    Vector2 direction = c1.position - rect_center;
    if (Vector2DotProduct(direction, normal) < 0)
        normal = {-normal.x, -normal.y};

    return {{normal}, depth};
}

/**
 * @brief Calculate a manifold between two colliders
 *
 * @param c1 circle collider
 * @param c2 rectangle collider
 *
 * @return CollisionManifold that consists from normal and depth
 */
const CollisionManifold GetCollisionManifold(const Collider& c1, const Collider& c2) {
    return std::visit([](auto const& a, auto const& b) { return GetCollisionManifold(a, b); }, c1,
                      c2);
}

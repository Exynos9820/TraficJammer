#include "CloverTree.h"
#include "RaylibExtCommon.h"
#include <numbers>
#include <raylib.h>

void CloverTree::Render() {
    const float& size = m_config.size;
    const Angle& rotation = m_config.rotation;
    Vector2 center_offset = m_position + Vector2(size / 2.0f, size / 2.0f);
    const float tree_radius = size * 0.3f;
    const Color center_color = {46, 125, 50, 255};
    const Color outer_circle_color = {150, 180, 100, 255};
    const Color inner_circle_color = {198, 221, 130, 255};

    // Draw top tree
    Vector2 top_tree_center = {size * 0.5f, size * 0.25f};
    Vector2 top_tree_absolute = m_position + top_tree_center;
    DrawCircleExt(top_tree_absolute, tree_radius, outer_circle_color);
    DrawCircleExt(top_tree_absolute, tree_radius / 2, inner_circle_color);

    // Draw left tree
    Vector2 left_tree_center = {size * 0.25f, size * 0.75f};
    Vector2 left_tree_absolute = m_position + left_tree_center;
    DrawCircleExt(left_tree_absolute, tree_radius, outer_circle_color);
    DrawCircleExt(left_tree_absolute, tree_radius / 2, inner_circle_color);

    // Draw right tree
    Vector2 right_tree_center = {size * 0.75f, size * 0.75f};
    Vector2 right_tree_absolute = m_position + right_tree_center;
    DrawCircleExt(right_tree_absolute, tree_radius, outer_circle_color);
    DrawCircleExt(right_tree_absolute, tree_radius / 2, inner_circle_color);

    // Draw 3 lines and circle in the center
    DrawCircleExt(center_offset, tree_radius / 4, center_color);
    Vector2 line{size * 0.35f, 0};
    DrawLineEx(center_offset, center_offset + RotateVector(line, std::numbers::pi * 0.25f),
               size / 20, center_color);
    DrawLineEx(center_offset, center_offset + RotateVector(line, std::numbers::pi * 0.75f),
               size / 20, center_color);
    DrawLineEx(center_offset, center_offset + RotateVector(line * 0.8, -std::numbers::pi * 0.5f),
               size / 20, center_color);

#ifdef DEBUG
    DrawCollider(GetCollider());
#endif
}

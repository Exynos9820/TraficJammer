#include "BushyTree.h"
#include "RaylibExtCommon.h"
#include <numbers>
#include <raylib.h>

void BushyTree::Render() {
    const float& size = m_config.size;
    const Angle& rotation = m_config.rotation;
    Vector2 center_offset = m_position + Vector2(size / 2.0f, size / 2.0f);
    const float tree_radius = size * 0.4f;
    const float bush_radius = size * 0.12f;
    const Color tree_circle_color = {150, 180, 100, 255};

    // Draw main circle
    DrawCircleExt(center_offset, tree_radius, tree_circle_color);

    // Draw bushes
    Vector2 line{size * 0.38f, 0};
    int num_bushes = 16;
    float radians_move = 2 * std::numbers::pi / num_bushes;
    for (int i = 0; i < num_bushes; i++) {
        DrawCircleExt(center_offset + RotateVector(line, radians_move * i), bush_radius,
                      tree_circle_color);
    }
}

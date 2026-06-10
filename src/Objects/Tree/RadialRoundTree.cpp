#include "RadialRoundTree.h"
#include "RaylibExtCommon.h"

void RadialRoundTree::Render() {
    const float& size = m_config.size;
    const Angle& rotation = m_config.rotation;
    Vector2 center_offset = m_position + Vector2(size / 2.0f, size / 2.0f);

    // Draw Main circle
    Color big_circle_color = {46, 125, 50, 255};
    DrawCircleExt(center_offset, size / 2.0f, big_circle_color);

    // Draw inner circle
    Color medium_circle_color = {150, 180, 100, 255};
    DrawCircleExt(center_offset, size * 0.42, medium_circle_color);

    Color inner_color = {198, 221, 130, 255};
    // Draw center circle
    DrawCircleExt(center_offset, size * 0.1f, inner_color);

    // Draw 6 lines
    Vector2 line{size * 0.35f, 0};
    for (int i = 0; i < 6; i++) {
        DrawLineEx(center_offset, center_offset + RotateVector(line, std::numbers::pi / 3 * i),
                   size / 30, inner_color);
    }

#ifdef DEBUG
    DrawCollider(GetCollider());
#endif
}

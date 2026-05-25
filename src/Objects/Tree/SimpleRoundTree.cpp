#include "SimpleRoundTree.h"
#include "RaylibExtCommon.h"

void SimpleRoundTree::Render() {
    const float& size = m_config.size;
    const Angle& rotation = m_config.rotation;
    Color big_circle_color = {132, 169, 93, 255};
    // Draw Main
    Vector2 big_circle_pos =
        m_position + RotateVector(Vector2(size / 2.0f, size / 2.0f), rotation.radians);
    DrawCircleExt(big_circle_pos, size / 2.0f, big_circle_color);
    // Draw second
    Color medium_circle_color = {150, 180, 100, 255};
    Vector2 medium_circle_pos =
        big_circle_pos + RotateVector(Vector2(-size / 8, -size / 8), rotation.radians);
    DrawCircleExt(medium_circle_pos, size / 4.0f, medium_circle_color);

    Color small_circle_color = {178, 201, 110, 255};
    Vector2 small_circle_pos =
        medium_circle_pos + RotateVector(Vector2(-size / 20, -size / 20), rotation.radians);
    DrawCircleExt(small_circle_pos, size / 10.0f, small_circle_color);
}

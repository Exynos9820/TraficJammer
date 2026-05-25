#include <cmath>
#include <raylib.h>

#include "Road.h"

void Road::Update(const std::chrono::microseconds& ms) {}

void Road::Render(const Vector2& position) {}

void Road::Render() {
    const Vector2 delta = m_config.start_left_top - m_position;
    const Vector2& left_bottom = m_config.start_left_bottom - delta;
    const Vector2& left_top = m_config.start_left_top - delta;
    const Vector2& right_bottom = m_config.start_right_bottom - delta;
    const Vector2& right_top = m_config.start_right_top - delta;
    const float& sides_thicknes = m_config.sides_thickness;
    const int& num_separators = m_config.num_separators;
    // Draw road rectangle
    auto recFromV = [](Vector2 pos, Vector2 size) -> Rectangle {
        return {
            .x = pos.x,
            .y = pos.y,
            .width = size.x,
            .height = size.y,
        };
    };

    // Draw Left and Right Sides of the road
    Vector2 left_side = left_top - left_bottom;
    float height = std::sqrt(left_side.x * left_side.x + left_side.y * left_side.y);
    Vector2 top_side = right_top - left_top;
    float width = std::sqrt(top_side.x * top_side.x + top_side.y * top_side.y);
    // calculate rotation
    Vector2 helping_point = {right_top.x, left_top.y};
    Vector2 helping_side = helping_point - left_top;
    float len_cat = std::sqrt(helping_side.x * helping_side.x + helping_side.y * helping_side.y);
    float rotation_rad = std::acos(len_cat / width);
    float rotation = (180 / std::numbers::pi) * rotation_rad;

    auto rec = recFromV(left_top, {width, height});
    DrawRectanglePro(rec, {0, 0}, rotation, LIGHTGRAY);

    DrawLineEx(left_top, right_top, sides_thicknes, DARKGRAY);
    DrawLineEx(left_bottom, right_bottom, sides_thicknes, DARKGRAY);

    // Draw separators for lines
    for (int i = 1; i < m_config.number_lanes; i++) {
        Vector2 start = (left_bottom - left_top) / m_config.number_lanes * i + left_top;
        Vector2 end = (right_bottom - right_top) / m_config.number_lanes * i + right_top;
        for (int i = 0; i < num_separators; i += 2) {
            Vector2 separator_start = (end - start) / num_separators * i + start;
            Vector2 separator_end = (end - start) / num_separators * (i + 1) + start;
            DrawLineEx(separator_start, separator_end, sides_thicknes, WHITE);
        }
    }
}

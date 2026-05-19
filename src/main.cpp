#include <chrono>
#include <thread>

#include "Config.h"
#include "raylib.h"
#include "Car.h"
#include "Player.h"

int main() {
    InitWindow(800, 600, "Traffic Jammer");
    SetTargetFPS(60);
    PlayerConfig config = GetDefaultPlayerConfig();
    // config.start_angle = 2;
    Player player{config};
    auto previous = std::chrono::high_resolution_clock::now();
    using namespace std::chrono_literals;
    while (!WindowShouldClose()) {
        auto now = std::chrono::high_resolution_clock::now();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        player.Render();
        player.Update(std::chrono::time_point_cast<std::chrono::microseconds>(now) -
                      std::chrono::time_point_cast<std::chrono::microseconds>(previous));
        DrawText("Traffic Jammer", 300, 280, 20, WHITE);
        EndDrawing();
        std::this_thread::sleep_for(10ms);
        previous = now;
    }

    CloseWindow();
    return 0;
}

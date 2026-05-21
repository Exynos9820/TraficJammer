#include <chrono>
#include <print>
#include <thread>

#include "Config.h"
#include "Road.h"
#include "raylib.h"
#include "Car.h"
#include "Player.h"

int main() {
    InitWindow(800, 600, "Traffic Jammer");
    SetTargetFPS(10000);
    PlayerConfig config = GetDefaultPlayerConfig();
    // config.start_angle = 2;
    Player player{config};
    Road road{GetDefaultRoadConfig()};
    int frames = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto previous = std::chrono::high_resolution_clock::now();
    using namespace std::chrono_literals;
    while (!WindowShouldClose()) {
        auto now = std::chrono::high_resolution_clock::now();
        BeginDrawing();
        ClearBackground(WHITE);
        road.Render();
        player.Render();
        frames++;
        player.Update(std::chrono::time_point_cast<std::chrono::microseconds>(now) -
                      std::chrono::time_point_cast<std::chrono::microseconds>(previous));
        DrawText("Traffic Jammer", 300, 280, 20, LIGHTGRAY);
        EndDrawing();
        // std::this_thread::sleep_for(10ms);
        previous = now;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto res = std::chrono::time_point_cast<std::chrono::milliseconds>(end) -
               std::chrono::time_point_cast<std::chrono::milliseconds>(start);
    std::println("Number of frames/s {}", frames * 1000.0 / res.count());

    CloseWindow();
    return 0;
}

#include <chrono>
#include <print>
#include <thread>

#include "BushyTree.h"
#include "CloverTree.h"
#include "Config.h"
#include "RadialRoundTree.h"
#include "Road.h"
#include "SimpleRoundTree.h"
#include "raylib.h"
#include "Car.h"
#include "Player.h"

int main() {
    InitWindow(800, 600, "Traffic Jammer");
    SetTargetFPS(120);
    PlayerConfig config = GetDefaultPlayerConfig();
    // config.start_angle = 2;
    Player player{config};
    Road road{GetDefaultRoadConfig()};
    SimpleRoundTree tree{GetDefaultTreeConfig()};
    TreeConfig config_tree = GetDefaultTreeConfig();
    config_tree.left_top_p.x += 60;
    RadialRoundTree tree2{config_tree};
    TreeConfig config_tree_2 = GetDefaultTreeConfig();
    config_tree.left_top_p.x += 60;
    CloverTree tree3{config_tree};
    TreeConfig config_tree_3 = GetDefaultTreeConfig();
    config_tree.left_top_p.x += 60;
    BushyTree tree4{config_tree};
    int frames = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto previous = std::chrono::high_resolution_clock::now();
    using namespace std::chrono_literals;
    while (!WindowShouldClose()) {
        auto now = std::chrono::high_resolution_clock::now();
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Traffic Jammer", 300, 280, 20, LIGHTGRAY);
        road.Render();
        player.Render();
        tree.Render();
        tree2.Render();
        tree3.Render();
        tree4.Render();
        frames++;
        player.Update(std::chrono::time_point_cast<std::chrono::microseconds>(now) -
                      std::chrono::time_point_cast<std::chrono::microseconds>(previous));
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

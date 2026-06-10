#include <chrono>
#include <print>
#include <thread>
#include <vector>

#include "BushyTree.h"
#include "CloverTree.h"
#include "CollisionManager.h"
#include "Config.h"
#include "Object.h"
#include "RadialRoundTree.h"
#include "Road.h"
#include "SimpleRoundTree.h"
#include "raylib.h"
#include "Car.h"
#include "Player.h"
#include "Grass.h"
#include "rlgl.h"

#define WIDTH 800
#define HEIGHT 600
#define num_grasses 10000

void run(CollisionManager* manager) {
    while (true) {
        manager->Update();
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Traffic Jammer");
    SetTargetFPS(60);
    PlayerConfig config = GetDefaultPlayerConfig();
    config.car_config.max_speed = 300;
    config.car_config.start_position = {WIDTH / 2.0f, HEIGHT / 2.0f};
    Player player{config};
    Road road{GetDefaultRoadConfig()};
    SimpleRoundTree tree{GetDefaultTreeConfig()};
    TreeConfig config_tree = GetDefaultTreeConfig();
    config_tree.start_left_top_p.x += 60;
    RadialRoundTree tree2{config_tree};
    TreeConfig config_tree_2 = GetDefaultTreeConfig();
    config_tree.start_left_top_p.x += 60;
    CloverTree tree3{config_tree};
    TreeConfig config_tree_3 = GetDefaultTreeConfig();
    config_tree.start_left_top_p.x += 60;
    BushyTree tree4{config_tree};
    int frames = 0;
    auto start = std::chrono::high_resolution_clock::now();
    auto previous = std::chrono::high_resolution_clock::now();
    using namespace std::chrono_literals;
    std::vector<Object*> objects = {&road, &tree, &tree2, &tree3, &tree4};
    CollisionManager* manager = CollisionManager::getInstance();
    manager->AddObject(&tree);
    manager->AddObject(&tree2);
    manager->AddObject(&tree3);
    manager->AddObject(&tree4);
    manager->AddObject(&player);
    std::thread t(run, manager);

    std::array<float, num_grasses * 9> grasses =
        Grass::GetGrassVertices<num_grasses>(WIDTH, HEIGHT);
    Mesh mesh = {0};
    mesh.vertexCount = num_grasses * 3;
    mesh.triangleCount = num_grasses;

    mesh.vertices = grasses.data();
    UploadMesh(&mesh, false);
    Model model = LoadModelFromMesh(mesh);
    Shader shader = LoadShader(SHADER_PATH "grass.vs", SHADER_PATH "grass.fs");
    model.materials[0].shader = shader;

    int mvpLoc = GetShaderLocation(shader, "mvp");
    Matrix projection = MatrixOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
    SetShaderValueMatrix(shader, mvpLoc, projection);

    int timeLoc = GetShaderLocation(shader, "u_time");
    int maxHeightLoc = GetShaderLocation(shader, "u_maxHeight");

    float maxHeight = 600.0f;
    SetShaderValue(shader, maxHeightLoc, &maxHeight, SHADER_UNIFORM_FLOAT);

    Vector2 resolution = {(float)GetScreenWidth(), (float)GetScreenHeight()};

    while (!WindowShouldClose()) {
        auto now = std::chrono::high_resolution_clock::now();
        float time = (float)GetTime();

        BeginDrawing();
        ClearBackground(DARKGREEN);
        BeginShaderMode(shader);
        SetShaderValueMatrix(shader, mvpLoc, projection);
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, maxHeightLoc, &maxHeight, SHADER_UNIFORM_FLOAT);

        rlEnableVertexArray(mesh.vaoId);
        rlDrawVertexArray(0, mesh.vertexCount);
        rlDisableVertexArray();
        EndShaderMode();

        DrawText("Traffic Jammer", 300, 280, 20, LIGHTGRAY);
        const auto ms = std::chrono::time_point_cast<std::chrono::microseconds>(now) -
                        std::chrono::time_point_cast<std::chrono::microseconds>(previous);
        const Vector2& move_vector = player.GetMoveVector(ms);
        for (const auto& object : objects) {
            object->Render();
            object->Move(move_vector);
        }
        player.Render();
        frames++;
        player.Update(ms);
        EndDrawing();
        previous = now;
    }
    t.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto res = std::chrono::time_point_cast<std::chrono::milliseconds>(end) -
               std::chrono::time_point_cast<std::chrono::milliseconds>(start);
    std::println("Number of frames/s {}", frames * 1000.0 / res.count());

    CloseWindow();
    return 0;
}

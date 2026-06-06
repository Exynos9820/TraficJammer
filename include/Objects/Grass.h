#include <array>
class Grass {
  public:
    template <int N> static std::array<float, N * 9> GetGrassVertices(int width, int height) {
        std::array<float, N * 9> grasses;
        for (int i = 0; i < N; i++) {
            float left_tip_x = (float)(rand() % width);
            float left_tip_y = (float)(rand() % height);
            float blade_height = 3.0f + (rand() % (height / 100));

            float right_tip_x = left_tip_x + 2;
            float right_tip_y = left_tip_y;

            float top_tip_x = left_tip_x + 1;
            float top_tip_y = left_tip_y + blade_height;

            grasses[i * 9] = left_tip_x;
            grasses[i * 9 + 1] = left_tip_y;
            grasses[i * 9 + 2] = 0.0f;

            grasses[i * 9 + 3] = right_tip_x;
            grasses[i * 9 + 4] = right_tip_y;
            grasses[i * 9 + 5] = 0.0f;

            grasses[i * 9 + 6] = top_tip_x;
            grasses[i * 9 + 7] = top_tip_y;
            grasses[i * 9 + 8] = 1.0f; // cheat code, set to 1 so we can check it later
        }
        return grasses;
    }
};

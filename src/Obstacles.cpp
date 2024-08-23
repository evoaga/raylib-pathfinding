
#include <vector>
#include <utility>
#include <cstdlib>
#include "Obstacles.hpp"

#include "Components.hpp"
#include "raylib.h"

auto generateObstaclesTransform(int count, float mapSize)
    -> std::vector<std::pair<TransformComponent, Obstacle>>
{
    std::vector<std::pair<TransformComponent, Obstacle>> obstacles;
    obstacles.reserve(count);
    float const halfMapSize = mapSize / 2.0F;

    for (int i = 0; i < count; ++i) {
        Vector3 const scale {0.5F + static_cast<float>(rand()) / RAND_MAX * 3.5F,
                             0.5F + static_cast<float>(rand()) / RAND_MAX * 3.5F,
                             0.5F + static_cast<float>(rand()) / RAND_MAX * 3.5F};
        Vector3 const position {static_cast<float>(rand()) / RAND_MAX * mapSize - halfMapSize,
                                scale.y / 2,
                                static_cast<float>(rand()) / RAND_MAX * mapSize - halfMapSize};
        Vector3 const rotation {0.0F, 0.0F, 0.0F};

        obstacles.emplace_back(TransformComponent {position, rotation, scale}, Obstacle {});
    }

    return obstacles;
}
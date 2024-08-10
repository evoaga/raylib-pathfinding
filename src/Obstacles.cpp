#include "Obstacles.hpp"
#include "NavMesh.hpp"
#include "Utils.hpp"
#include "ThetaStar.hpp"

auto generateObstaclesTransform(int count, float mapSize) -> std::vector<std::pair<TransformComponent, Obstacle>>
{
    std::vector<std::pair<TransformComponent, Obstacle>> obstacles;
    obstacles.reserve(count);
    const float halfMapSize = mapSize / 2.0f;

    for (int i = 0; i < count; ++i)
    {
        Vector3 scale{
            0.5f + static_cast<float>(rand()) / RAND_MAX * 3.5f,
            0.5f + static_cast<float>(rand()) / RAND_MAX * 3.5f,
            0.5f + static_cast<float>(rand()) / RAND_MAX * 3.5f};
        Vector3 position{
            static_cast<float>(rand()) / RAND_MAX * mapSize - halfMapSize,
            scale.y / 2,
            static_cast<float>(rand()) / RAND_MAX * mapSize - halfMapSize};
        Vector3 rotation{
            0.0f,
            0.0f,
            0.0f};

        obstacles.push_back({TransformComponent{position, rotation, scale}, Obstacle{}});
    }

    return obstacles;
}
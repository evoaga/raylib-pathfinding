#pragma once

#include <utility>

#include "Components/Components.hpp"

auto generateObstaclesTransform(int count, float mapSize)
    -> std::vector<std::pair<TransformComponent, Obstacle>>;
void saveObstaclesToJsonFile(const std::vector<std::pair<TransformComponent, Obstacle>> &obstacles,
                             const std::string &filename);
auto loadObstaclesFromJsonFile(const std::string &filename)
    -> std::vector<std::pair<TransformComponent, Obstacle>>;

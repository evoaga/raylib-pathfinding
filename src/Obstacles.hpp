#pragma once

#include <utility>

#include "Components/Components.hpp"

auto generateObstaclesTransform(int count, float mapSize)
    -> std::vector<std::pair<TransformComponent, Obstacle>>;

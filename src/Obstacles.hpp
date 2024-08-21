#pragma once

#include "Components/Components.hpp"
#include <utility>

auto generateObstaclesTransform(int count, float mapSize) -> std::vector<std::pair<TransformComponent, Obstacle>>;

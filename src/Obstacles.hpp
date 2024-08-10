#pragma once

#include "Components/Components.hpp"
#include "ThetaStar.hpp"
#include "raylib.h"
#include <vector>

std::vector<std::pair<TransformComponent, Obstacle>> generateObstaclesTransform(int count, float mapSize);
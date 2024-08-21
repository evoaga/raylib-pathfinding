#pragma once

#include "raylib.h"

#include <entt/entt.hpp>

void UpdateMinionPath(entt::registry &registry, const Vector3 &playerPosition);
void MinionSystem(entt::registry &registry);
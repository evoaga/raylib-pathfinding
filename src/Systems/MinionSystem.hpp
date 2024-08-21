#pragma once

#include <entt/entt.hpp>
#include "raylib.h"

void UpdateMinionPath(entt::registry &registry, const Vector3 &playerPosition);
void MinionSystem(entt::registry &registry);
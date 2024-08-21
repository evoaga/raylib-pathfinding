#pragma once

#include "raylib.h"

#include <entt/entt.hpp>

void InitCamera(Camera &camera);
void CameraSystem(entt::registry &registry);

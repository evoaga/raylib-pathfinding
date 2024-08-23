#pragma once

#include <entt/entt.hpp>

#include "entt/entity/fwd.hpp"
#include "raylib.h"

void InitCamera(Camera &camera);
void CameraSystem(entt::registry &registry);

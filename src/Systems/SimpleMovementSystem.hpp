#include <entt/entt.hpp>
#include "../Utils.hpp"
#include "../Components/Components.hpp"
#include "raylib.h"
#include <cmath>

auto SimpleMovementSystem(entt::registry &registry) -> void
{
    auto view = registry.view<Player, TransformComponent, Speed>();

    view.each([&](entt::entity, auto &transform, auto &speed)
              {
        Vector3 direction = { 0.0f, 0.0f, 0.0f };
        
        if (IsKeyDown(KEY_UP)) direction.z -= 1.0f;
        if (IsKeyDown(KEY_DOWN)) direction.z += 1.0f;
        if (IsKeyDown(KEY_LEFT)) direction.x -= 1.0f;
        if (IsKeyDown(KEY_RIGHT)) direction.x += 1.0f;

        float length = Vector3Length(direction);
        if (length != 0) {
            direction = Vector3Scale(direction, 1.0f / length);
            Vector3 movement = Vector3Scale(direction, speed.value * GetFrameTime());
            transform.position = Vector3Add(transform.position, movement);
        } });
}

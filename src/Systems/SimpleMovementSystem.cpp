#include <cmath>

#include <entt/entt.hpp>

#include "../Components/Components.hpp"
#include "../VectorMath.hpp"
#include "entt/entity/fwd.hpp"
#include "raylib.h"

auto SimpleMovementSystem(entt::registry &registry) -> void
{
    auto view = registry.view<Player, TransformComponent, Speed>();

    view.each(
        [&](entt::entity, auto &transform, auto &speed)
        {
            Vector3 direction = {0.0F, 0.0F, 0.0F};

            if (IsKeyDown(KEY_UP)) {
                direction.z -= 1.0F;
            }
            if (IsKeyDown(KEY_DOWN)) {
                direction.z += 1.0F;
            }
            if (IsKeyDown(KEY_LEFT)) {
                direction.x -= 1.0F;
            }
            if (IsKeyDown(KEY_RIGHT)) {
                direction.x += 1.0F;
            }

            float const length = Vector3Length(direction);
            if (length != 0) {
                direction = Vector3Scale(direction, 1.0F / length);
                Vector3 const movement = Vector3Scale(direction, speed.value * GetFrameTime());
                transform.position = Vector3Add(transform.position, movement);
            }
        });
}

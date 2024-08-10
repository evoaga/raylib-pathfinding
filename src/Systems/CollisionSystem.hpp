#pragma once

#include <entt/entt.hpp>
#include "raylib.h"
#include "../Components/Components.hpp"
#include "../VectorMath.hpp"
#include "../Utils.hpp"
#include <algorithm>

auto CollisionSystem(entt::registry &registry) -> void
{
    auto view = registry.view<TransformComponent, CollisionComponent>();
    auto obstacleView = registry.view<TransformComponent, Obstacle>();

    view.each([&](entt::entity, auto &transform, auto &collision)
              {
        bool collided = false;
        for (auto obstacleEntity : obstacleView) {
            auto& obstacleTransform = obstacleView.get<TransformComponent>(obstacleEntity);
            if (CheckCollisionAABB(transform.position, transform.scale, obstacleTransform.position, obstacleTransform.scale)) {
                collided = true;
                break;
            }
        }
        collision.collided = collided; });
}

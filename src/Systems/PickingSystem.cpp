#include "../Components/Components.hpp"
#include "../VectorMath.hpp"

#include "raylib.h"
#include <entt/entt.hpp>

auto PickingSystem(entt::registry &registry) -> void
{
    auto cameraView = registry.view<CameraComponent>();
    auto &camera = cameraView.get<CameraComponent>(cameraView.front()).camera;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Ray ray = GetMouseRay(GetMousePosition(), camera);
        bool foundSelection = false;

        auto obstacleView = registry.view<TransformComponent, Obstacle, Selected>();

        obstacleView.each([&](entt::entity /*entity*/, auto &transform, auto &, auto &selected)
                          {
            BoundingBox const box = {
                Vector3Subtract(transform.position, Vector3Scale(transform.scale, 0.5F)),
                Vector3Add(transform.position, Vector3Scale(transform.scale, 0.5F))
            };

            RayCollision const collision = GetRayCollisionBox(ray, box);

            if (collision.hit && !foundSelection) {
                selected.isSelected = true;
                foundSelection = true;
            } else {
                selected.isSelected = false;
            } });
    }
}

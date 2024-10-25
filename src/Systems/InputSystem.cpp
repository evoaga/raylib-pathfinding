#include "InputSystem.hpp"

#include "../Components/Components.hpp"
#include "../Engine.hpp"
#include "../Utils.hpp"
#include "entt/entity/fwd.hpp"
#include "raylib.h"

auto InputSystem(entt::registry &registry) -> void
{
    auto playerView = registry.view<Player, PathComponent>();
    auto cameraView = registry.view<CameraComponent>();

    cameraView.each(
        [&](CameraComponent &cameraComponent)
        {
            playerView.each(
                [&](entt::entity, PathComponent &pathComponent)
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        pathComponent.goalSet = true;
                        pathComponent.goalPos = GetMousePosition3D(cameraComponent.camera);
                        pathComponent.updateRequested = true;
                    }
                });

            if (IsKeyPressed(KEY_Y)) {
                cameraComponent.attached = !cameraComponent.attached;
            }
        });

    if (IsKeyPressed(KEY_R)) {
        registry.clear();
        Engine::InitEntities(registry);
    }
}

#include "InputSystem.hpp"
#include "../Components/Components.hpp"
#include "../Engine.hpp"
#include "../Utils.hpp"

#include "raylib.h"

auto InputSystem(entt::registry &registry) -> void
{
    auto playerView = registry.view<Player, Health, PathComponent>();
    auto cameraView = registry.view<CameraComponent>();

    cameraView.each([&](CameraComponent &cameraComponent)
                    {
        playerView.each([&](entt::entity, Health& health, PathComponent& pathComponent) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                pathComponent.goalSet = true;
                pathComponent.goalPos = GetMousePosition3D(cameraComponent.camera);
                pathComponent.updateRequested = true;
            }

            if (IsKeyPressed(KEY_E)) {
                health.value -= 10;
                if (health.value < 0) {
                    health.value = 0;
                }
            }
        });

        if (IsKeyPressed(KEY_Y)) {
            cameraComponent.attached = !cameraComponent.attached;
        } });

    if (IsKeyPressed(KEY_R))
    {
        registry.clear();
        Engine::InitEntities(registry);
    }
}

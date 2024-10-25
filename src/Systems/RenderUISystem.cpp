#include "RenderUISystem.hpp"

#include "../Components/Components.hpp"
#include "entt/entity/fwd.hpp"
#include "raylib.h"

auto RenderUISystem(entt::registry &registry) -> void
{
    auto drawSelectedObstacleInfo = [&](int entityID, const Vector3 &position, float size)
    {
        DrawText(TextFormat("Obstacle ID: %d", entityID), 10, 30, 20, BLACK);
        DrawText(TextFormat("Position: [%.2f, %.2f, %.2f]", position.x, position.y, position.z),
                 10,
                 50,
                 20,
                 BLACK);
        DrawText(TextFormat("Size: %.2f", size), 10, 70, 20, BLACK);
    };

    auto drawUI = [&](entt::registry &)
    {
        auto view = registry.view<Player, TransformComponent>();
        for (auto entity : view) {
            auto &transform = view.get<TransformComponent>(entity);

            // Draw player coordinates
            int const screenWidth = GetScreenWidth();
            int const screenHeight = GetScreenHeight();
            std::string const positionText = TextFormat("Position: (%.2f, %.2f, %.2f)",
                                                        transform.position.x,
                                                        transform.position.y,
                                                        transform.position.z);
            int const textWidth = MeasureText(positionText.c_str(), 20);
            DrawText(
                positionText.c_str(), screenWidth - textWidth - 10, screenHeight - 30, 20, BLACK);
        }
    };

    auto renderEntityIDs =
        [&](auto entity, TransformComponent &transform, CameraComponent &cameraComponent)
    {
        Vector2 const screenPos = GetWorldToScreen(transform.position, cameraComponent.camera);
        DrawText(TextFormat("%d", static_cast<uint32_t>(entity)),
                 static_cast<int>(screenPos.x),
                 static_cast<int>(screenPos.y),
                 20,
                 BLACK);
    };

    // Start drawing UI

    auto cameraView = registry.view<CameraComponent>();
    cameraView.each(
        [&](CameraComponent &cameraComponent)
        {
            auto entityIDView = registry.view<TransformComponent>();
            entityIDView.each([&](auto entity, TransformComponent &transform)
                              { renderEntityIDs(entity, transform, cameraComponent); });
        });

    drawUI(registry);

    auto selectedObstacleView = registry.view<TransformComponent, Obstacle, Selected>();
    selectedObstacleView.each(
        [&](auto entity, auto &transform, auto &, auto &selected)
        {
            if (selected.isSelected) {
                drawSelectedObstacleInfo(
                    static_cast<uint32_t>(entity), transform.position, transform.scale.x);
            }
        });

    DrawFPS(10, 10);
}

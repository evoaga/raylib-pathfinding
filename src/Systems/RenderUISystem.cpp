#include "RenderUISystem.hpp"

#include "../Components/Components.hpp"
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

    auto drawHealthBarAboveEntity =
        [&](const Vector3 &position, const Health &health, const Camera &camera)
    {
        Vector2 const screenPos = GetWorldToScreen(position, camera);
        float const healthPercentage = static_cast<float>(health.value) / health.maxValue;

        int const barWidth = 50;
        int const barHeight = 10;
        int const barX = static_cast<int>(screenPos.x) - barWidth / 2;
        int const barY = static_cast<int>(screenPos.y) - 40;

        DrawRectangle(barX, barY, barWidth, barHeight, GRAY);
        DrawRectangle(barX, barY, static_cast<int>(barWidth * healthPercentage), barHeight, RED);
        DrawText(TextFormat("%d / %d", health.value, health.maxValue), barX, barY - 10, 10, BLACK);
    };

    auto drawHealthBar = [&](int health, int maxHealth)
    {
        int const screenWidth = GetScreenWidth();
        int const screenHeight = GetScreenHeight();
        float const healthPercentage = static_cast<float>(health) / static_cast<float>(maxHealth);

        int const barWidth = 300;
        int const barHeight = 20;

        int const barX = (screenWidth - barWidth) / 2;
        int const barY = screenHeight - 50;

        DrawRectangleLines(barX, barY, barWidth, barHeight, BLACK);
        DrawRectangle(barX + 1, barY + 1, barWidth - 2, barHeight - 2, GRAY);

        int const healthBarWidth = static_cast<int>((barWidth - 2) * healthPercentage);
        DrawRectangle(barX + 1, barY + 1, healthBarWidth, barHeight - 2, RED);
        DrawText(
            TextFormat("%d / %d", health, maxHealth),
            barX + (barWidth / 2) - MeasureText(TextFormat("%d / %d", health, maxHealth), 20) / 2,
            barY,
            20,
            BLACK);
    };

    auto drawUI = [&](entt::registry &)
    {
        auto view = registry.view<Player, Health, TransformComponent>();
        for (auto entity : view) {
            auto &health = view.get<Health>(entity);
            auto &transform = view.get<TransformComponent>(entity);

            drawHealthBar(health.value, health.maxValue);

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

    auto renderHealthBars =
        [&](TransformComponent &transform, Health &health, CameraComponent &cameraComponent)
    { drawHealthBarAboveEntity(transform.position, health, cameraComponent.camera); };

    // Start drawing UI

    auto cameraView = registry.view<CameraComponent>();
    cameraView.each(
        [&](CameraComponent &cameraComponent)
        {
            auto entityIDView = registry.view<TransformComponent>();
            entityIDView.each([&](auto entity, TransformComponent &transform)
                              { renderEntityIDs(entity, transform, cameraComponent); });

            auto healthBarView = registry.view<TransformComponent, Health>();
            healthBarView.each([&](TransformComponent &transform, Health &health)
                               { renderHealthBars(transform, health, cameraComponent); });
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

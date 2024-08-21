#include "RenderSystem.hpp"
#include "../Components/Components.hpp"
#include "../ThetaStar.hpp"

#include "raylib.h"

auto RenderSystem(entt::registry &registry) -> void
{
    auto renderPlatforms = [&](TransformComponent &transform)
    {
        (void)transform;
        DrawGrid(80, 1.0F);
    };

    auto renderPlayers = [&](TransformComponent &transform)
    {
        DrawCube(transform.position, transform.scale.x, transform.scale.z, transform.scale.y, BLUE);
        DrawCubeWires(transform.position, transform.scale.x, transform.scale.y, transform.scale.z, DARKBLUE);
    };

    auto renderMinions = [&](TransformComponent &transform, Minion &minion)
    {
        (void)minion;

        DrawCube(transform.position, transform.scale.x, transform.scale.z, transform.scale.y, RED);
        DrawCubeWires(transform.position, transform.scale.x, transform.scale.z, transform.scale.y, MAROON);
    };

    auto renderObstacles = [&](TransformComponent &transform, Obstacle &obstacle, Selected &selected)
    {
        // Generate a random color
        Color const color = selected.isSelected ? RED : obstacle.color;

        Color const wireColor = selected.isSelected ? MAROON : DARKGRAY;
        Color const selectionColor = selected.isSelected ? GREEN : DARKGRAY;

        DrawCube(transform.position, transform.scale.x, transform.scale.y, transform.scale.z, color);
        DrawCubeWires(transform.position, transform.scale.x, transform.scale.y, transform.scale.z, wireColor);
        if (selected.isSelected)
        {
            DrawCubeWires(transform.position, transform.scale.x + 0.2F, transform.scale.y + 0.2F, transform.scale.z + 0.2F, selectionColor);
        }
    };

    auto renderNavMesh = [&](NavMeshComponent &navmeshComponent)
    {
        const auto &mesh = navmeshComponent.mesh;

        for (const auto &vertex : mesh.vertices)
        {
            DrawCube({vertex.x, vertex.y, vertex.z}, 0.1F, 0.1F, 0.1F, DARKGRAY);
        }
    };

    auto renderPlayerGoals = [&](PathComponent &pathComponent)
    {
        if (pathComponent.goalSet)
        {
            DrawCircle3D(pathComponent.goalPos, 0.5F, {1, 0, 0}, 90.0F, BLUE);
            DrawLine3D(pathComponent.start, pathComponent.end, RED);

            if (!pathComponent.path.empty())
            {
                for (size_t i = 0; i < pathComponent.path.size() - 1; ++i)
                {
                    Vector3 const start = {pathComponent.path[i].x, pathComponent.path[i].y, pathComponent.path[i].z};
                    Vector3 const end = {pathComponent.path[i + 1].x, pathComponent.path[i + 1].y, pathComponent.path[i + 1].z};
                    DrawLine3D(start, end, PURPLE);
                }
            }
        }
    };

    // Entity views for different components
    auto cameraView = registry.view<CameraComponent>();
    auto platformView = registry.view<TransformComponent, Platform>();
    auto playerView = registry.view<TransformComponent, Player>();
    auto playerGoalView = registry.view<Player, PathComponent>();
    auto minionsView = registry.view<TransformComponent, Minion>();
    auto obstacleView = registry.view<TransformComponent, Obstacle, Selected>();
    auto navmeshView = registry.view<NavMeshComponent>();

    cameraView.each([&](CameraComponent & /*cameraComponent*/)
                    {
                        platformView.each(renderPlatforms);
                        playerView.each(renderPlayers);
                        minionsView.each(renderMinions);
                        obstacleView.each(renderObstacles);
                        navmeshView.each(renderNavMesh);
                        playerGoalView.each(renderPlayerGoals); });
}
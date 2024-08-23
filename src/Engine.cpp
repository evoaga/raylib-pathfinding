
#include <entt/entt.hpp>

#include "Components/Components.hpp"
#include "NavMesh.hpp"
#include "Obstacles.hpp"
#include "Systems/CameraSystem.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/MinionSystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/PickingSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/RenderUISystem.hpp"
#include "ThetaStar.hpp"
#include "Utils.hpp"
#include "entt/entity/fwd.hpp"
#include "raylib.h"

namespace Engine
{

auto InitEntities(entt::registry &registry) -> void
{
    // Create player entity
    const auto player = registry.create();
    registry.emplace<TransformComponent>(
        player,
        TransformComponent {
            Vector3 {0.0F, 1.0F, 0.0F}, Vector3 {0.0F, 0.0F, 0.0F}, Vector3 {1.0F, 1.0F, 1.0F}});
    registry.emplace<Health>(player, 100, 100);
    registry.emplace<Speed>(player, 5.0F);
    registry.emplace<PathComponent>(player,
                                    PathComponent {Vector3 {0.0F, 0.0F, 0.0F},
                                                   Vector3 {0.0F, 0.0F, 0.0F},
                                                   Vector3 {0.0F, 0.0F, 0.0F},
                                                   {}});
    registry.emplace<Player>(player);

    // Create camera entity
    const auto cameraEntity = registry.create();
    Camera camera;
    InitCamera(camera);
    auto cameraComponent = CameraComponent {camera, true, 1.0F};
    registry.emplace<CameraComponent>(cameraEntity, cameraComponent);

    // Create minions
    for (int i = 0; i < 5; ++i) {
        const auto minion = registry.create();
        registry.emplace<TransformComponent>(
            minion,
            TransformComponent {Vector3 {static_cast<float>(i) * 2.0F, 1.0F, 0.0F},
                                Vector3 {0.0F, 0.0F, 0.0F},
                                Vector3 {0.5F, 0.5F, 0.5F}});
        registry.emplace<Health>(minion, 50, 50);
        registry.emplace<Speed>(minion, 4.0F);
        registry.emplace<PathComponent>(minion,
                                        PathComponent {Vector3 {0.0F, 0.0F, 0.0F},
                                                       Vector3 {0.0F, 0.0F, 0.0F},
                                                       Vector3 {0.0F, 0.0F, 0.0F},
                                                       {},
                                                       false});
        registry.emplace<Minion>(minion, i);
    }

    // Create platform entity
    const auto platform = registry.create();
    registry.emplace<TransformComponent>(
        platform,
        TransformComponent {
            Vector3 {0.0F, 0.0F, 0.0F}, Vector3 {0.0F, 0.0F, 0.0F}, Vector3 {10.0F, 1.0F, 10.0F}});
    registry.emplace<Platform>(platform);

    // Create navmesh entity
    const auto navmeshEntity = registry.create();
    auto obstacles = generateObstaclesTransform(120, 80.0F);

    std::vector<Polygon> obstaclePolygons;
    for (const auto &[transform, type] : obstacles) {
        Polygon polygon;
        polygon = generateCubePolygon(transform);
        obstaclePolygons.push_back(polygon);
    }

    NavMesh mesh;
    BuildNavMesh(mesh, obstaclePolygons);
    registry.emplace<NavMeshComponent>(navmeshEntity, NavMeshComponent {mesh, obstaclePolygons});

    // Create obstacles
    for (const auto &[transform, type] : obstacles) {
        const auto obstacleEntity = registry.create();
        registry.emplace<TransformComponent>(obstacleEntity, transform);
        registry.emplace<Obstacle>(obstacleEntity, GetRandomColor());
        registry.emplace<Selected>(obstacleEntity, false);
    }
}

auto Run() -> void
{
    InitWindow(1200, 900, "entt-raylib");

    entt::registry registry;
    InitEntities(registry);

    while (!WindowShouldClose()) {
        auto cameraView = registry.view<CameraComponent>();
        auto &cameraComponent = cameraView.get<CameraComponent>(cameraView.front());

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(cameraComponent.camera);

        PickingSystem(registry);
        InputSystem(registry);
        MinionSystem(registry);
        MovementSystem(registry);

        MovementSystem(registry);
        PathfindingSystem(registry);

        CameraSystem(registry);

        RenderSystem(registry);
        EndMode3D();

        RenderUISystem(registry);

        EndDrawing();
    }

    CloseWindow();
}

}  // namespace Engine

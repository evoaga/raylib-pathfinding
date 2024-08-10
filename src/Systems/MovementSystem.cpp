#include "MovementSystem.hpp"
#include "../Utils.hpp"
#include "../Components/Components.hpp"
#include "../NavMesh.hpp"
#include "../Obstacles.hpp"
#include "../VectorMath.hpp"
#include "../Polygons.hpp"
#include "raylib.h"
#include <cmath>

auto MovementSystem(entt::registry &registry) -> void
{
    auto playerView = registry.view<Player, TransformComponent, Speed, PathComponent, CollisionComponent>();
    auto obstacleView = registry.view<TransformComponent, Obstacle>();
    auto navMeshView = registry.view<NavMeshComponent>();

    playerView.each([&](entt::entity, auto &transform, auto &speed, auto &pathComponent, auto &collision)
                    {
        if (!pathComponent.goalSet) return;

        auto updatePath = [&]() {
            pathComponent.path.clear();
            pathComponent.isPathBlocked = false;
            pathComponent.currentPathIndex = 0;
            pathComponent.start = transform.position;
            pathComponent.end = pathComponent.goalPos;
        };

        auto moveEntity = [&](const Vector3& targetPos) {
            Vector3 direction = Vector3Subtract(targetPos, transform.position);
            float distance = Vector3Length(direction);
            if (distance < 0.1f) {
                transform.position = targetPos;
                pathComponent.currentPathIndex++;
                if (pathComponent.currentPathIndex >= pathComponent.path.size()) {
                    transform.position = pathComponent.goalPos;
                    pathComponent.goalSet = false;
                    pathComponent.isPathBlocked = false;
                }
            } else {
                direction = Vector3Scale(direction, 1.0f / distance);
                Vector3 movement = Vector3Scale(direction, speed.value * GetFrameTime());
                transform.position = Vector3Add(transform.position, movement);
            }
        };

        auto &navMeshComponent = navMeshView.get<NavMeshComponent>(*navMeshView.begin());

        if (isPointInAnyPolygon(pathComponent.goalPos, navMeshComponent.obstaclePolygons)) {
            pathComponent.goalPos = findNearestValidPoint(pathComponent.goalPos, navMeshComponent.obstaclePolygons, 0.5f);
        }
        
        if (!Vector3Equals(pathComponent.goalPos, pathComponent.end)) {
            updatePath();
        }

        if (pathComponent.isPathBlocked && !pathComponent.path.empty()) {
            moveEntity({
                pathComponent.path[pathComponent.currentPathIndex].x,
                pathComponent.path[pathComponent.currentPathIndex].y,
                pathComponent.path[pathComponent.currentPathIndex].z
            });
            return;
        }

        Vector3 direction = Vector3Subtract(pathComponent.goalPos, transform.position);
        float distance = Vector3Length(direction);
        direction = Vector3Scale(direction, 1.0f / distance);
        Vector3 movement = Vector3Scale(direction, speed.value * GetFrameTime());
        Vector3 newPosition = Vector3Add(transform.position, movement);

        if (distance < Vector3Length(movement)) {
            transform.position = pathComponent.goalPos;
            pathComponent.goalSet = false;
            return;
        }

        if (!collision.collided) {
            transform.position = newPosition;
        }

        bool isPathBlocked = false;

        for (const auto &polygon : navMeshComponent.obstaclePolygons)
        {
            // Convert Vector3 to Point
            Point startPoint = vector3ToPoint(transform.position);
            Point goalPoint = vector3ToPoint(pathComponent.goalPos);

            if (lineIntersectsPolygon(startPoint, goalPoint, polygon))
            {
                isPathBlocked = true;
                break;
            }
        }

        if (isPathBlocked && pathComponent.updateRequested) {
            // Collect obstacle positions
            std::vector<Vector3> obstaclePositions;
            for (auto obstacleEntity : obstacleView) {
                auto& obstacleTransform = obstacleView.get<TransformComponent>(obstacleEntity);
                obstaclePositions.push_back(obstacleTransform.position);
            }

            Point start = { transform.position.x, transform.position.y, transform.position.z };
            Point goal = { pathComponent.goalPos.x, pathComponent.goalPos.y, pathComponent.goalPos.z };

            pathComponent.path = thetaStar(navMeshComponent.mesh, start, goal, navMeshComponent.obstaclePolygons);

            pathComponent.isPathBlocked = true;
            pathComponent.currentPathIndex = 0;
            pathComponent.start = transform.position;
            pathComponent.updateRequested = false;
        } });
}

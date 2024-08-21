#include <entt/entt.hpp>
#include "../Utils.hpp"
#include "../Components/Components.hpp"
#include "../VectorMath.hpp"
#include "../Polygons.hpp"
#include "../ThetaStar.hpp"

#include "raylib.h"
#include <cmath>
#include <vector>

auto UpdateMinionPath(entt::registry &registry, const Vector3 &playerPosition) -> void
{
    auto minionView = registry.view<Minion, TransformComponent, PathComponent>();
    auto obstacleView = registry.view<TransformComponent, Obstacle>();
    auto navMeshView = registry.view<NavMeshComponent>();

    minionView.each([&](entt::entity, auto &minion, auto &transform, auto &pathComponent)
                    {
        (void)minion;

        const Vector3 newGoalPos = playerPosition;
        const float distanceToNewGoal = Vector3Distance(pathComponent.goalPos, newGoalPos);

        // Update goal position if the player has moved significantly
        if (distanceToNewGoal > 1.0F)
        {
            pathComponent.goalPos = newGoalPos;

            // Check if the path to the goal is blocked
            bool isPathBlocked = false;
            for (const auto &navMeshEntity : navMeshView)
            {
                const auto &navMeshComponent = navMeshView.get<NavMeshComponent>(navMeshEntity);
                for (const auto &polygon : navMeshComponent.obstaclePolygons)
                {
                    // Convert Vector3 to Point
                    Point const startPoint = vector3ToPoint(transform.position);
                    Point const goalPoint = vector3ToPoint(pathComponent.goalPos);

                    if (lineIntersectsPolygon(startPoint, goalPoint, polygon))
                    {
                        isPathBlocked = true;
                        break;
                    }
                }
                if (isPathBlocked) {
                    break;
                }
            }

            if (isPathBlocked)
            {
                // Update path using thetaStar if the path is blocked
                std::vector<Vector3> obstaclePositions;
                for (auto obstacleEntity : obstacleView)
                {
                    const auto &obstacleTransform = obstacleView.get<TransformComponent>(obstacleEntity);
                    obstaclePositions.push_back(obstacleTransform.position);
                }

                Point const start = {transform.position.x, transform.position.y, transform.position.z};
                Point const goal = {pathComponent.goalPos.x, pathComponent.goalPos.y, pathComponent.goalPos.z};

                pathComponent.path = thetaStar(navMeshView.get<NavMeshComponent>(*navMeshView.begin()).mesh, start, goal, navMeshView.get<NavMeshComponent>(*navMeshView.begin()).obstaclePolygons);

                pathComponent.currentPathIndex = 0;
                pathComponent.start = transform.position;
            }
            else
            {
                // Clear the path if the path is not blocked
                pathComponent.path.clear();
            }
        } });
}

auto MoveMinion(entt::registry &registry) -> void
{
    auto minionView = registry.view<Minion, TransformComponent, Speed, PathComponent>();

    minionView.each([&](entt::entity, auto &minion, auto &transform, auto &speed, auto &pathComponent)
                    {
        (void)minion;

        // Move directly towards the goal if the path is clear
        if (pathComponent.path.empty())
        {
            const Vector3 direction = Vector3Normalize(Vector3Subtract(pathComponent.goalPos, transform.position));
            const Vector3 movement = Vector3Scale(direction, speed.value * GetFrameTime());
            transform.position = Vector3Add(transform.position, movement);
        }
        else
        {
            // Move along the path
            const Vector3 targetPos = {pathComponent.path[pathComponent.currentPathIndex].x,
                                       pathComponent.path[pathComponent.currentPathIndex].y,
                                       pathComponent.path[pathComponent.currentPathIndex].z};

            const Vector3 direction = Vector3Subtract(targetPos, transform.position);
            const float distance = Vector3Length(direction);

            if (distance < 0.1F)
            {
                transform.position = targetPos;
                pathComponent.currentPathIndex++;
                if (pathComponent.currentPathIndex >= pathComponent.path.size())
                {
                    transform.position = pathComponent.goalPos;
                    pathComponent.path.clear();
                }
            }
            else
            {
                const Vector3 normalizedDirection = Vector3Scale(direction, 1.0F / distance);
                const Vector3 movement = Vector3Scale(normalizedDirection, speed.value * GetFrameTime());
                transform.position = Vector3Add(transform.position, movement);
            }
        } });
}

auto MinionSystem(entt::registry &registry) -> void
{
    auto playerView = registry.view<Player, TransformComponent>();

    const entt::entity playerEntity = *playerView.begin();
    const auto &playerTransform = playerView.get<TransformComponent>(playerEntity);

    UpdateMinionPath(registry, playerTransform.position);
    MoveMinion(registry);
}

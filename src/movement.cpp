#include "Movement.hpp"
#include "Player.hpp"

void moveAlongPath(const std::vector<Point>& path, std::vector<Point>::size_type& currentPathIndex, Player& player, bool& isMoving) {
    if (isMoving && currentPathIndex < path.size()) {
        Vector3 targetPosition = {path[currentPathIndex].x, path[currentPathIndex].y, path[currentPathIndex].z};
        Vector3 direction = Vector3Subtract(targetPosition, player.getPosition());
        float distance = Vector3Length(direction);
        float moveSpeed = player.getSpeed();
        float frameTime = GetFrameTime();

        if (distance > 0.1f) {
            direction = Vector3Scale(Vector3Normalize(direction), moveSpeed * frameTime);
            Vector3 newPosition = Vector3Add(player.getPosition(), direction);
            player.setPosition(newPosition.x, newPosition.y, newPosition.z);
        } else {
            player.setPosition(targetPosition.x, targetPosition.y, targetPosition.z);
            currentPathIndex++;
        }

        if (currentPathIndex >= path.size()) {
            isMoving = false;
        }
    }
}

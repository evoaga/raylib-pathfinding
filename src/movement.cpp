#include "movement.hpp"

void moveAlongPath(std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, Vector3& currentPositionThetaStar, bool& isMovingThetaStar) {
    if (isMovingThetaStar && currentPathIndexThetaStar < pathThetaStar.size()) {
        Vector3 targetPosition = {pathThetaStar[currentPathIndexThetaStar].x, pathThetaStar[currentPathIndexThetaStar].y, pathThetaStar[currentPathIndexThetaStar].z};
        Vector3 direction = Vector3Subtract(targetPosition, currentPositionThetaStar);
        float distance = Vector3Length(direction);
        float moveSpeed = 3.0f; 
        float frameTime = GetFrameTime();

        if (distance > 0.1f) {
            direction = Vector3Scale(Vector3Normalize(direction), moveSpeed * frameTime);
            currentPositionThetaStar = Vector3Add(currentPositionThetaStar, direction);
        } else {
            currentPositionThetaStar = targetPosition;
            currentPathIndexThetaStar++;
        }
    }
}

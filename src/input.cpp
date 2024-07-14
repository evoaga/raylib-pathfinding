#include "Input.hpp"
#include "raylib.h"
#include "NavMesh.hpp"
#include "Obstacles.hpp"
#include "thetastar.hpp"
#include "utils.hpp"
#include "GameObject.hpp"

void HandleKeyPressR(std::vector<GameObject>& obstacles, NavMesh& mesh, std::vector<Point>& initialPoints, std::vector<Polygon>& polygons, Point& goal, bool& goalSet, GameObject& player, float obstacleSize, std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, bool& isMovingThetaStar) {
    if (IsKeyPressed(KEY_R)) {
        updateObstacles(obstacles, mesh, initialPoints, polygons, goal, goalSet, player, obstacleSize, pathThetaStar);
        currentPathIndexThetaStar = 0;
        isMovingThetaStar = false;
    }
}

void HandleMouseInput(const Camera3D& camera, std::vector<Point>& initialPoints, NavMesh& mesh, std::vector<GameObject>& obstacles, float obstacleSize, std::vector<Polygon>& polygons, Point& goal, bool& goalSet, GameObject& player, std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, bool& isMovingThetaStar) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector3 mousePosition = GetMousePosition3D(camera);
        goal = Point(mousePosition.x, mousePosition.y, mousePosition.z);

        std::vector<Vector3> obstaclePositions;
        for (const auto& obstacle : obstacles) {
            obstaclePositions.push_back(obstacle.getPosition());
        }

        goal = findNearestValidPoint(goal, obstaclePositions, obstacleSize);
        goalSet = true;

        Vector3 goalVec = {goal.x, goal.y, goal.z};
        bool obstacleInPath = false;

        for (const auto& pos : obstaclePositions) {
            if (segmentIntersectsObstacle(player.getPosition(), goalVec, pos, obstacleSize)) {
                obstacleInPath = true;
                break;
            }
        }

        if (obstacleInPath) {
            std::vector<Point> pointsWithGoalAndCurrent = initialPoints;
            pointsWithGoalAndCurrent.push_back(goal);
            pointsWithGoalAndCurrent.push_back(Point(player.getPosition().x, player.getPosition().y, player.getPosition().z));
            updateNavMesh(mesh, pointsWithGoalAndCurrent, obstaclePositions, obstacleSize, polygons);

            Point currentPointThetaStar(player.getPosition().x, player.getPosition().y, player.getPosition().z);
            pathThetaStar = thetaStar(mesh, currentPointThetaStar, goal, obstaclePositions, obstacleSize);
            currentPathIndexThetaStar = 0;
            isMovingThetaStar = true;
        } else {
            pathThetaStar = { Point(player.getPosition().x, player.getPosition().y, player.getPosition().z), goal };
            currentPathIndexThetaStar = 0;
            isMovingThetaStar = true;
        }
    }
}

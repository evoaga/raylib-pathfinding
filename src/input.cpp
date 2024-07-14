#include "input.hpp"
#include "raylib.h"
#include "nav_mesh.hpp"
#include "obstacles.hpp"
#include "thetastar.hpp"
#include "utils.hpp"

void HandleKeyPressR(std::vector<Vector3>& obstaclePositions, NavMesh& mesh, std::vector<Point>& initialPoints, std::vector<Polygon>& polygons, Point& goal, bool& goalSet, Vector3& currentPositionThetaStar, float obstacleSize, std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, bool& isMovingThetaStar) {
    if (IsKeyPressed(KEY_R)) {
        updateObstacles(obstaclePositions, mesh, initialPoints, polygons, goal, goalSet, currentPositionThetaStar, obstacleSize, pathThetaStar);
        currentPathIndexThetaStar = 0;
        isMovingThetaStar = false;
    }
}

void HandleMouseInput(const Camera3D& camera, std::vector<Point>& initialPoints, NavMesh& mesh, std::vector<Vector3>& obstaclePositions, float obstacleSize, std::vector<Polygon>& polygons, Point& goal, bool& goalSet, Vector3& currentPositionThetaStar, std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, bool& isMovingThetaStar) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector3 mousePosition = GetMousePosition3D(camera);
        goal = Point(mousePosition.x, mousePosition.y, mousePosition.z);

        goal = findNearestValidPoint(goal, obstaclePositions, obstacleSize);
        goalSet = true;

        Vector3 goalVec = {goal.x, goal.y, goal.z};
        bool obstacleInPath = false;

        for (const auto& pos : obstaclePositions) {
            if (segmentIntersectsObstacle(currentPositionThetaStar, goalVec, pos, obstacleSize)) {
                obstacleInPath = true;
                break;
            }
        }

        if (obstacleInPath) {
            std::vector<Point> pointsWithGoalAndCurrent = initialPoints;
            pointsWithGoalAndCurrent.push_back(goal);
            pointsWithGoalAndCurrent.push_back(Point(currentPositionThetaStar.x, currentPositionThetaStar.y, currentPositionThetaStar.z));
            updateNavMesh(mesh, pointsWithGoalAndCurrent, obstaclePositions, obstacleSize, polygons);

            Point currentPointThetaStar(currentPositionThetaStar.x, currentPositionThetaStar.y, currentPositionThetaStar.z);
            pathThetaStar = thetaStar(mesh, currentPointThetaStar, goal, obstaclePositions, obstacleSize);
            currentPathIndexThetaStar = 0;
            isMovingThetaStar = true;
        } else {
            pathThetaStar = { Point(currentPositionThetaStar.x, currentPositionThetaStar.y, currentPositionThetaStar.z), goal };
            currentPathIndexThetaStar = 0;
            isMovingThetaStar = true;
        }
    }
}

#include "obstacles.hpp"

void updateObstacles(std::vector<Vector3>& obstaclePositions, NavMesh& mesh, const std::vector<Point>& initialPoints, std::vector<Polygon>& polygons, Point& goal, bool goalSet, Vector3& currentPositionThetaStar, float obstacleSize, std::vector<Point>& pathThetaStar) {
    obstaclePositions = generateObstaclePositions(5, 10.0f);
    updateNavMesh(mesh, initialPoints, obstaclePositions, obstacleSize, polygons);
    if (goalSet) {
        std::vector<Point> pointsWithGoal = initialPoints;
        pointsWithGoal.push_back(goal);
        pointsWithGoal.push_back(Point(currentPositionThetaStar.x, currentPositionThetaStar.y, currentPositionThetaStar.z));
        updateNavMesh(mesh, pointsWithGoal, obstaclePositions, obstacleSize, polygons);
        Point currentPointThetaStar(currentPositionThetaStar.x, currentPositionThetaStar.y, currentPositionThetaStar.z);
        pathThetaStar = thetaStar(mesh, currentPointThetaStar, goal, obstaclePositions, obstacleSize);
    }
}

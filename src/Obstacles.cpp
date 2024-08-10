#include "Obstacles.hpp"

void updateObstacles(std::vector<GameObject> &obstacles, NavMesh &mesh, const std::vector<Point> &initialPoints, std::vector<Polygon> &polygons, Point &goal, bool goalSet, GameObject &player, float obstacleSize, std::vector<Point> &pathThetaStar)
{
    obstacles = generateObstaclePositions(5, 10.0f);

    std::vector<Vector3> obstaclePositions;
    for (const auto &obstacle : obstacles)
    {
        obstaclePositions.push_back(obstacle.getPosition());
    }

    updateNavMesh(mesh, initialPoints, obstaclePositions, obstacleSize, polygons);

    Vector3 currentPositionThetaStar = player.getPosition();

    if (goalSet)
    {
        std::vector<Point> pointsWithGoal = initialPoints;
        pointsWithGoal.push_back(goal);
        pointsWithGoal.push_back(Point(currentPositionThetaStar.x, currentPositionThetaStar.y, currentPositionThetaStar.z));
        updateNavMesh(mesh, pointsWithGoal, obstaclePositions, obstacleSize, polygons);

        Point currentPointThetaStar(currentPositionThetaStar.x, currentPositionThetaStar.y, currentPositionThetaStar.z);
        pathThetaStar = thetaStar(mesh, currentPointThetaStar, goal, obstaclePositions, obstacleSize);
    }
}

std::vector<GameObject> generateObstaclePositions(int count, float mapSize)
{
    std::vector<GameObject> obstacles;
    obstacles.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        float x = static_cast<float>(rand() % static_cast<int>(mapSize));
        float z = static_cast<float>(rand() % static_cast<int>(mapSize));
        obstacles.emplace_back(x, 0.5f, z);
    }
    return obstacles;
}

// Function to check if a ray intersects with an obstacle
bool segmentIntersectsObstacle(Vector3 start, Vector3 end, const Vector3 &obstacle, float obstacleSize)
{
    BoundingBox box = {
        {obstacle.x - obstacleSize / 2, obstacle.y - obstacleSize / 2, obstacle.z - obstacleSize / 2},
        {obstacle.x + obstacleSize / 2, obstacle.y + obstacleSize / 2, obstacle.z + obstacleSize / 2}};

    return CheckCollisionSegmentBox(start, end, box);
}
#include "thetastar.hpp"
#include "Obstacles.hpp"

void NavMesh::addVertex(const Point& p) {
    vertices.push_back(p);
}

void NavMesh::addEdge(const Point& p1, const Point& p2, float cost) {
    edges.emplace_back(p1, p2, cost);
}

void NavMesh::clear() {
    vertices.clear();
    edges.clear();
}

float heuristic(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) +
                     std::pow(p1.y - p2.y, 2) +
                     std::pow(p1.z - p2.z, 2));
}

bool lineOfSight(const Point& s, const Point& sPrime, const std::vector<Vector3>& obstaclePositions, float obstacleSize) {
    Vector3 start = {s.x, s.y, s.z};
    Vector3 end = {sPrime.x, sPrime.y, sPrime.z};
    for (const auto& obstacle : obstaclePositions) {
        if (segmentIntersectsObstacle(start, end, obstacle, obstacleSize)) {
            return false;
        }
    }
    return true;
}

std::vector<Point> thetaStar(const NavMesh& mesh, const Point& start, const Point& goal, const std::vector<Vector3>& obstaclePositions, float obstacleSize) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    std::unordered_map<Point, Point, PointHash> cameFrom;
    std::unordered_map<Point, float, PointHash> gScore;
    std::unordered_map<Point, float, PointHash> fScore;

    auto inf = std::numeric_limits<float>::infinity();
    for (const auto& vertex : mesh.vertices) {
        gScore[vertex] = inf;
        fScore[vertex] = inf;
    }

    gScore[start] = 0.0f;
    fScore[start] = heuristic(start, goal);

    openList.emplace(start, gScore[start], fScore[start]);
    cameFrom[start] = start;

    while (!openList.empty()) {
        Point current = openList.top().point;
        openList.pop();

        if (current == goal) {
            // Reconstruct path
            std::vector<Point> path;
            while (cameFrom[current] != current) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& edge : mesh.edges) {
            if (edge.p1 == current || edge.p2 == current) {
                Point neighbor = (edge.p1 == current) ? edge.p2 : edge.p1;
                Point parent = cameFrom[current];

                if (lineOfSight(parent, neighbor, obstaclePositions, obstacleSize)) {
                    float tentative_gScore = gScore[parent] + heuristic(parent, neighbor);
                    if (tentative_gScore < gScore[neighbor]) {
                        cameFrom[neighbor] = parent;
                        gScore[neighbor] = tentative_gScore;
                        fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, goal);
                        openList.emplace(neighbor, gScore[neighbor], fScore[neighbor]);
                    }
                } else {
                    float tentative_gScore = gScore[current] + edge.cost;
                    if (tentative_gScore < gScore[neighbor]) {
                        cameFrom[neighbor] = current;
                        gScore[neighbor] = tentative_gScore;
                        fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, goal);
                        openList.emplace(neighbor, gScore[neighbor], fScore[neighbor]);
                    }
                }
            }
        }
    }

    // Return empty path if no path is found
    return std::vector<Point>();
}

bool isPointInsideObstacle(const Point& point, const Vector3& obstacle, float obstacleSize) {
    float halfSize = obstacleSize / 2;
    Vector3 min = {obstacle.x - halfSize, 0.0f, obstacle.z - halfSize};
    Vector3 max = {obstacle.x + halfSize, 0.0f, obstacle.z + halfSize};

    return (point.x > min.x && point.x < max.x && point.z > min.z && point.z < max.z);
}

Point findNearestValidPoint(const Point& point, const std::vector<Vector3>& obstaclePositions, float obstacleSize) {
    float minDistance = FLT_MAX;
    Point nearestPoint = point;

    for (const auto& obstacle : obstaclePositions) {
        if (isPointInsideObstacle(point, obstacle, obstacleSize)) {
            float halfSize = obstacleSize / 2.0f;
            float buffer = 0.15f;
            // Define points on the perimeter of the obstacle with buffer
            std::vector<Point> perimeterPoints = {
                Point(obstacle.x - halfSize - buffer, 0.0f, point.z),
                Point(obstacle.x + halfSize + buffer, 0.0f, point.z),
                Point(point.x, 0.0f, obstacle.z - halfSize - buffer),
                Point(point.x, 0.0f, obstacle.z + halfSize + buffer)
            };

            for (const auto& perimeterPoint : perimeterPoints) {
                float distance = Vector3Length(Vector3Subtract(Vector3{perimeterPoint.x, perimeterPoint.y, perimeterPoint.z}, Vector3{point.x, point.y, point.z}));
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPoint = perimeterPoint;
                }
            }
        }
    }

    return nearestPoint;
}

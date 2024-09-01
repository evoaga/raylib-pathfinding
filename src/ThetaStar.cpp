#include "ThetaStar.hpp"

#include "Polygons.hpp"

auto heuristic(const Point &p1, const Point &p2) -> float
{
    return static_cast<float>(
        std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2) + std::pow(p1.z - p2.z, 2)));
}

auto lineOfSight(const Point &s, const Point &sPrime, const std::vector<Polygon> &polygons) -> bool
{
    // Check for intersection with polygons
    for (const auto &polygon : polygons) {
        if (lineIntersectsPolygonLoS(s, sPrime, polygon)) {
            return false;
        }
    }
    return true;
}

auto thetaStar(NavMesh &mesh,
               const Point &start,
               const Point &goal,
               const std::vector<Polygon> &obstaclePolygons) -> std::vector<Point>
{
    mesh.addVertex(start);
    mesh.addVertex(goal);

    std::priority_queue<Node, std::vector<Node>, std::greater<>> openList;
    std::unordered_map<Point, Point, PointHash> cameFrom;
    std::unordered_map<Point, float, PointHash> gScore;
    std::unordered_map<Point, float, PointHash> fScore;

    auto inf = std::numeric_limits<float>::infinity();
    for (const auto &vertex : mesh.vertices) {
        gScore[vertex] = inf;
        fScore[vertex] = inf;
    }

    gScore[start] = 0.0F;
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

            mesh.removeVertex(start);
            mesh.removeVertex(goal);

            return path;
        }

        for (const auto &neighbor : mesh.vertices) {
            if (neighbor != current && lineOfSight(current, neighbor, obstaclePolygons)) {
                Point const parent = cameFrom[current];

                if (lineOfSight(parent, neighbor, obstaclePolygons)) {
                    float const tentative_gScore = gScore[parent] + heuristic(parent, neighbor);
                    if (tentative_gScore < gScore[neighbor]) {
                        cameFrom[neighbor] = parent;
                        gScore[neighbor] = tentative_gScore;
                        fScore[neighbor] = gScore[neighbor] + heuristic(neighbor, goal);
                        openList.emplace(neighbor, gScore[neighbor], fScore[neighbor]);
                    }
                } else {
                    float const tentative_gScore = gScore[current] + heuristic(current, neighbor);
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

    mesh.removeVertex(start);
    mesh.removeVertex(goal);

    // Return empty path if no path is found
    return {};
}
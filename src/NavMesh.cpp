#include "NavMesh.hpp"
#include "delaunator.hpp"

bool edgeIntersectsObstacle(const Edge &edge, const Vector3 &obstacle, float obstacleSize)
{
    float halfSize = obstacleSize / 2;
    Vector3 min = {obstacle.x - halfSize, 0.0f, obstacle.z - halfSize};
    Vector3 max = {obstacle.x + halfSize, 0.0f, obstacle.z + halfSize};

    return (min.x <= std::max(edge.p1.x, edge.p2.x) && max.x >= std::min(edge.p1.x, edge.p2.x) &&
            min.z <= std::max(edge.p1.z, edge.p2.z) && max.z >= std::min(edge.p1.z, edge.p2.z));
}

void initializeNavMesh(NavMesh &mesh, const std::vector<Point> &initialPoints, const std::vector<Vector3> &obstaclePositions, float obstacleSize, std::vector<Polygon> &polygons)
{
    std::vector<Point> points = initialPoints;
    points.reserve(initialPoints.size() + obstaclePositions.size() * 4);

    float buffer = 0.2f;
    float halfSize = obstacleSize / 2;
    for (const auto &pos : obstaclePositions)
    {
        points.emplace_back(pos.x - halfSize - buffer, 0.0f, pos.z - halfSize - buffer);
        points.emplace_back(pos.x + halfSize + buffer, 0.0f, pos.z - halfSize - buffer);
        points.emplace_back(pos.x - halfSize - buffer, 0.0f, pos.z + halfSize + buffer);
        points.emplace_back(pos.x + halfSize + buffer, 0.0f, pos.z + halfSize + buffer);
    }

    std::vector<double> coords;
    coords.reserve(points.size() * 2);
    for (const auto &point : points)
    {
        coords.push_back(point.x);
        coords.push_back(point.z);
    }

    delaunator::Delaunator delaunator(coords);

    for (const auto &point : points)
    {
        mesh.addVertex(point);
    }

    const size_t trianglesSize = delaunator.triangles.size();
    for (size_t i = 0; i < trianglesSize; i += 3)
    {
        const Point &p1 = points[delaunator.triangles[i]];
        const Point &p2 = points[delaunator.triangles[i + 1]];
        const Point &p3 = points[delaunator.triangles[i + 2]];

        Edge e1(p1, p2, heuristic(p1, p2));
        Edge e2(p2, p3, heuristic(p2, p3));
        Edge e3(p3, p1, heuristic(p3, p1));

        bool intersect1 = false, intersect2 = false, intersect3 = false;

        for (const auto &obstacle : obstaclePositions)
        {
            if (!intersect1 && edgeIntersectsObstacle(e1, obstacle, obstacleSize))
                intersect1 = true;
            if (!intersect2 && edgeIntersectsObstacle(e2, obstacle, obstacleSize))
                intersect2 = true;
            if (!intersect3 && edgeIntersectsObstacle(e3, obstacle, obstacleSize))
                intersect3 = true;
            if (intersect1 && intersect2 && intersect3)
                break;
        }

        if (!intersect1)
            mesh.addEdge(e1.p1, e1.p2, e1.cost);
        if (!intersect2)
            mesh.addEdge(e2.p1, e2.p2, e2.cost);
        if (!intersect3)
            mesh.addEdge(e3.p1, e3.p2, e3.cost);

        if (!intersect1 && !intersect2 && !intersect3)
        {
            polygons.push_back({{p1, p2, p3}});
        }
    }
}

void updateNavMesh(NavMesh &mesh, const std::vector<Point> &additionalPoints, const std::vector<Vector3> &obstaclePositions, float obstacleSize, std::vector<Polygon> &polygons)
{
    mesh.clear();
    polygons.clear();
    std::vector<Point> points = additionalPoints;
    points.reserve(additionalPoints.size() + obstaclePositions.size() * 4);

    float buffer = 0.2f;
    float halfSize = obstacleSize / 2;
    for (const auto &pos : obstaclePositions)
    {
        points.emplace_back(pos.x - halfSize - buffer, 0.0f, pos.z - halfSize - buffer);
        points.emplace_back(pos.x + halfSize + buffer, 0.0f, pos.z - halfSize - buffer);
        points.emplace_back(pos.x - halfSize - buffer, 0.0f, pos.z + halfSize + buffer);
        points.emplace_back(pos.x + halfSize + buffer, 0.0f, pos.z + halfSize + buffer);
    }

    std::vector<double> coords;
    coords.reserve(points.size() * 2);
    for (const auto &point : points)
    {
        coords.push_back(point.x);
        coords.push_back(point.z);
    }

    delaunator::Delaunator delaunator(coords);

    for (const auto &point : points)
    {
        mesh.addVertex(point);
    }

    const size_t trianglesSize = delaunator.triangles.size();
    for (size_t i = 0; i < trianglesSize; i += 3)
    {
        const Point &p1 = points[delaunator.triangles[i]];
        const Point &p2 = points[delaunator.triangles[i + 1]];
        const Point &p3 = points[delaunator.triangles[i + 2]];

        Edge e1(p1, p2, heuristic(p1, p2));
        Edge e2(p2, p3, heuristic(p2, p3));
        Edge e3(p3, p1, heuristic(p3, p1));

        bool intersect1 = false, intersect2 = false, intersect3 = false;

        for (const auto &obstacle : obstaclePositions)
        {
            if (!intersect1 && edgeIntersectsObstacle(e1, obstacle, obstacleSize))
                intersect1 = true;
            if (!intersect2 && edgeIntersectsObstacle(e2, obstacle, obstacleSize))
                intersect2 = true;
            if (!intersect3 && edgeIntersectsObstacle(e3, obstacle, obstacleSize))
                intersect3 = true;
            if (intersect1 && intersect2 && intersect3)
                break;
        }

        if (!intersect1)
            mesh.addEdge(e1.p1, e1.p2, e1.cost);
        if (!intersect2)
            mesh.addEdge(e2.p1, e2.p2, e2.cost);
        if (!intersect3)
            mesh.addEdge(e3.p1, e3.p2, e3.cost);

        if (!intersect1 && !intersect2 && !intersect3)
        {
            polygons.push_back({{p1, p2, p3}});
        }
    }
}

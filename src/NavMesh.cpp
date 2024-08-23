
#include "NavMesh.hpp"

#include "Polygons.hpp"
#include "ThetaStar.hpp"

auto BuildNavMesh(NavMesh &mesh, std::vector<Polygon> &obstaclePolygons) -> void
{
    std::vector<Point> obstaclePoints;
    std::vector<double> coords;

    // Extract points from polygons
    for (const auto &polygon : obstaclePolygons) {
        for (const auto &point : polygon.vertices) {
            obstaclePoints.push_back(point);
            coords.push_back(point.x);
            coords.push_back(point.z);
        }
    }

    for (const auto &point : obstaclePoints) {
        mesh.addVertex(point);
    }

    for (auto &polygon : obstaclePolygons) {
        sortPolygonClockwise(polygon);
    }
}
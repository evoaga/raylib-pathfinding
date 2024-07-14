#ifndef NAV_MESH_HPP
#define NAV_MESH_HPP

#include <vector>
#include "raylib.h"
#include "thetastar.hpp"

// Forward declare Delaunator
namespace delaunator {
    class Delaunator;
}

struct Polygon {
    std::vector<Point> vertices;
};

void initializeNavMesh(NavMesh& mesh, const std::vector<Point>& initialPoints, const std::vector<Vector3>& obstaclePositions, float obstacleSize, std::vector<Polygon>& polygons);
void updateNavMesh(NavMesh& mesh, const std::vector<Point>& additionalPoints, const std::vector<Vector3>& obstaclePositions, float obstacleSize, std::vector<Polygon>& polygons);

#endif

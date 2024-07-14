#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "raylib.h"
#include "nav_mesh.hpp"

void drawScene(const NavMesh& mesh, const std::vector<Polygon>& polygons, const std::vector<Vector3>& obstaclePositions, float obstacleSize, const Vector3& currentPositionThetaStar, bool goalSet, const Point& goal, const std::vector<Point>& pathThetaStar, const Camera3D& camera);

#endif

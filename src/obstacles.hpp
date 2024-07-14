#ifndef OBSTACLES_HPP
#define OBSTACLES_HPP

#include <vector>
#include "raylib.h"
#include "nav_mesh.hpp"

void updateObstacles(std::vector<Vector3>& obstaclePositions, NavMesh& mesh, const std::vector<Point>& initialPoints, std::vector<Polygon>& polygons, Point& goal, bool goalSet, Vector3& currentPositionThetaStar, float obstacleSize, std::vector<Point>& pathThetaStar);

#endif

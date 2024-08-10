#ifndef OBSTACLES_HPP
#define OBSTACLES_HPP

#include "NavMesh.hpp"
#include "GameObject.hpp"
#include "ThetaStar.hpp"
#include "raylib.h"
#include <vector>

void updateObstacles(std::vector<GameObject> &obstacles, NavMesh &mesh, const std::vector<Point> &initialPoints, std::vector<Polygon> &polygons, Point &goal, bool goalSet, GameObject &player, float obstacleSize, std::vector<Point> &pathThetaStar);
std::vector<GameObject> generateObstaclePositions(int count, float mapSize);
bool segmentIntersectsObstacle(Vector3 start, Vector3 end, const Vector3 &obstacle, float obstacleSize);

#endif // OBSTACLES_HPP

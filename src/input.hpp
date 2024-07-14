#ifndef INPUT_HPP
#define INPUT_HPP

#include "raylib.h"
#include "nav_mesh.hpp"
#include "obstacles.hpp"
#include <vector>

void HandleKeyPressR(std::vector<Vector3>& obstaclePositions, NavMesh& mesh, std::vector<Point>& initialPoints, std::vector<Polygon>& polygons, Point& goal, bool& goalSet, Vector3& currentPositionThetaStar, float obstacleSize, std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, bool& isMovingThetaStar);
void HandleMouseInput(const Camera3D& camera, std::vector<Point>& initialPoints, NavMesh& mesh, std::vector<Vector3>& obstaclePositions, float obstacleSize, std::vector<Polygon>& polygons, Point& goal, bool& goalSet, Vector3& currentPositionThetaStar, std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, bool& isMovingThetaStar);

#endif // INPUT_HPP

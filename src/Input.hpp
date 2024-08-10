#ifndef INPUT_HPP
#define INPUT_HPP

#include "raylib.h"
#include "NavMesh.hpp"
#include "GameObject.hpp"
#include <vector>

void HandleKeyPressR(std::vector<GameObject> &obstacles, NavMesh &mesh, std::vector<Point> &initialPoints, std::vector<Polygon> &polygons, Point &goal, bool &goalSet, GameObject &player, float obstacleSize, std::vector<Point> &pathThetaStar, std::vector<Point>::size_type &currentPathIndexThetaStar, bool &isMovingThetaStar);

void HandleMouseInput(const Camera3D &camera, std::vector<Point> &initialPoints, NavMesh &mesh, std::vector<GameObject> &obstacles, float obstacleSize, std::vector<Polygon> &polygons, Point &goal, bool &goalSet, GameObject &player, std::vector<Point> &pathThetaStar, std::vector<Point>::size_type &currentPathIndexThetaStar, bool &isMovingThetaStar);

#endif // INPUT_HPP

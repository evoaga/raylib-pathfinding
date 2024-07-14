#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <vector>
#include "raylib.h"
#include "thetastar.hpp"

void moveAlongPath(std::vector<Point>& pathThetaStar, std::vector<Point>::size_type& currentPathIndexThetaStar, Vector3& currentPositionThetaStar, bool& isMovingThetaStar);

#endif

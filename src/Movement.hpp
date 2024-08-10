#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "raylib.h"
#include "GameObject.hpp"
#include "ThetaStar.hpp"
#include "Player.hpp"
#include <vector>

void moveAlongPath(const std::vector<Point> &path, std::vector<Point>::size_type &currentPathIndex, Player &player, bool &isMoving);

#endif // MOVEMENT_HPP

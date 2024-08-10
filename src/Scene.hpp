#ifndef SCENE_HPP
#define SCENE_HPP

#include "raylib.h"
#include "NavMesh.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include <vector>

void DrawHealthBarAbovePlayer(const Player &player, const Camera &camera);
void DrawHealthBar(const Player &player);
void DrawUI();
void DrawScene(const NavMesh &mesh, const std::vector<Polygon> &polygons, const std::vector<GameObject> &obstacles, float obstacleSize, const Player &player, bool goalSet, const Point &goal, const std::vector<Point> &pathThetaStar, const Camera &camera);

#endif // SCENE_HPP

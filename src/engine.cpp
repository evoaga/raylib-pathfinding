#include "Engine.hpp"
#include "NavMesh.hpp"
#include "Obstacles.hpp"
#include "Movement.hpp"
#include "thetastar.hpp"
#include "Input.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "utils.hpp"
#include "raylib.h"
#include "GameObject.hpp"
#include "Player.hpp"
#include "PlayerFactory.hpp"
#include <ctime>
#include <vector>

namespace Engine {

void InitWindowAndSeed(int screenWidth, int screenHeight) {
    InitWindow(screenWidth, screenHeight, "3D Navigation Mesh Theta* Visualization");
    srand(static_cast<unsigned int>(time(0)));
}

std::vector<Point> InitInitialPoints() {
    return {
        Point(0.0f, 0.0f, 0.0f),
        Point(10.0f, 2.0f, 0.0f),
        Point(10.0f, 0.0f, 10.0f),
        Point(0.0f, -2.0f, 10.0f)
    };
}

NavMesh InitNavMesh(std::vector<Point>& initialPoints, std::vector<GameObject>& obstacles, float obstacleSize, std::vector<Polygon>& polygons) {
    std::vector<Vector3> obstaclePositions;
    for (const auto& obstacle : obstacles) {
        obstaclePositions.push_back(obstacle.getPosition());
    }
    NavMesh mesh;
    initializeNavMesh(mesh, initialPoints, obstaclePositions, obstacleSize, polygons);
    return mesh;
}

void Run() {
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindowAndSeed(screenWidth, screenHeight);

    auto initialPoints = InitInitialPoints();
    auto obstacles = generateObstaclePositions(5, 10.0f);
    float obstacleSize = 1.0f;

    std::vector<Polygon> polygons;
    auto mesh = InitNavMesh(initialPoints, obstacles, obstacleSize, polygons);

    Player player = PlayerFactory::createPlayer(5.0f, 0.0f, 5.0f);
    Point goal;
    bool goalSet = false;
    bool cameraAttached = true;

    std::vector<Point> pathThetaStar;
    std::vector<Point>::size_type currentPathIndexThetaStar = 0;
    bool isMovingThetaStar = false;

    Camera camera = InitCamera();

    while (!WindowShouldClose()) {
        HandleCameraMovement(camera, player.getPosition(), cameraAttached);
        HandleKeyPressR(obstacles, mesh, initialPoints, polygons, goal, goalSet, player, obstacleSize, pathThetaStar, currentPathIndexThetaStar, isMovingThetaStar);
        HandleMouseInput(camera, initialPoints, mesh, obstacles, obstacleSize, polygons, goal, goalSet, player, pathThetaStar, currentPathIndexThetaStar, isMovingThetaStar);
        moveAlongPath(pathThetaStar, currentPathIndexThetaStar, player, isMovingThetaStar);

        if (IsKeyPressed(KEY_E)) {
            player.takeDamage(20);
        }

        if (!player.isAlive()) {
            if (player.shouldRespawn()) {
                player.respawn(Vector3{5.0f, 0.0f, 5.0f}, 100);
            }
        }

        DrawScene(mesh, polygons, obstacles, obstacleSize, player, goalSet, goal, pathThetaStar, camera);
    }

    CloseWindow();
}

} // namespace Engine

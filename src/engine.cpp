// engine.cpp
#include "engine.hpp"
#include "nav_mesh.hpp"
#include "obstacles.hpp"
#include "movement.hpp"
#include "thetastar.hpp"
#include "input.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "utils.hpp"
#include "raylib.h"
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

std::vector<Vector3> InitObstaclePositions(int count, float range) {
    return generateObstaclePositions(count, range);
}

NavMesh InitNavMesh(std::vector<Point>& initialPoints, std::vector<Vector3>& obstaclePositions, float obstacleSize, std::vector<Polygon>& polygons) {
    NavMesh mesh;
    initializeNavMesh(mesh, initialPoints, obstaclePositions, obstacleSize, polygons);
    return mesh;
}

void Run() {
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindowAndSeed(screenWidth, screenHeight);

    auto initialPoints = InitInitialPoints();
    auto obstaclePositions = InitObstaclePositions(5, 10.0f);
    float obstacleSize = 1.0f;

    std::vector<Polygon> polygons;
    auto mesh = InitNavMesh(initialPoints, obstaclePositions, obstacleSize, polygons);

    Point start(5.0f, 0.0f, 5.0f);
    Point goal;
    bool goalSet = false;
    bool cameraAttached = true;

    std::vector<Point> pathThetaStar;
    std::vector<Point>::size_type currentPathIndexThetaStar = 0;
    Vector3 currentPositionThetaStar = {start.x, start.y, start.z};
    bool isMovingThetaStar = false;

    Camera camera = InitCamera();

    while (!WindowShouldClose()) {
        HandleCameraMovement(camera, currentPositionThetaStar, cameraAttached);
        HandleKeyPressR(obstaclePositions, mesh, initialPoints, polygons, goal, goalSet, currentPositionThetaStar, obstacleSize, pathThetaStar, currentPathIndexThetaStar, isMovingThetaStar);
        HandleMouseInput(camera, initialPoints, mesh, obstaclePositions, obstacleSize, polygons, goal, goalSet, currentPositionThetaStar, pathThetaStar, currentPathIndexThetaStar, isMovingThetaStar);
        moveAlongPath(pathThetaStar, currentPathIndexThetaStar, currentPositionThetaStar, isMovingThetaStar);
        drawScene(mesh, polygons, obstaclePositions, obstacleSize, currentPositionThetaStar, goalSet, goal, pathThetaStar, camera);
    }

    CloseWindow();
}

} // namespace Engine

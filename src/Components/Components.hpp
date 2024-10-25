#pragma once

#include <cstddef>
#include <vector>

#include <entt/entt.hpp>

#include "../ThetaStar.hpp"
#include "raylib.h"

struct CameraComponent
{
    Camera camera;
    bool attached;
    float zoomLevel;
};

struct Player
{
};

struct Platform
{
};

struct Obstacle
{
    Color color;
};

struct Minion
{
    int id;
};

struct TransformComponent
{
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    TransformComponent()
        : position({0, 0, 0})
        , rotation({0, 0, 0})
        , scale({1, 1, 1})
    {
    }

    TransformComponent(Vector3 pos, Vector3 rot, Vector3 scl)
        : position(pos)
        , rotation(rot)
        , scale(scl)
    {
    }
};

struct Speed
{
    float value;
};

struct NavMeshComponent
{
    NavMesh mesh;
    std::vector<Polygon> obstaclePolygons;
};

struct PathComponent
{
    Vector3 start;
    Vector3 end;

    Vector3 goalPos;

    std::vector<Point> path;

    bool goalSet = false;
    bool updateRequested = false;
    bool isPathBlocked = false;
    size_t currentPathIndex = 0;
};

struct Selected
{
    bool isSelected;
};

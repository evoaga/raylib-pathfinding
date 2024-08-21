#pragma once

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <cfloat>
#include <utility>
#include <vector>

struct Point
{
    float x, y, z;

    // Default constructor
    Point() : x(0), y(0), z(0) {}

    // Parameterized constructor
    Point(float x, float y, float z) : x(x), y(y), z(z) {}

    auto operator==(const Point &other) const -> bool
    {
        return x == other.x && y == other.y && z == other.z;
    }

    auto operator!=(const Point &other) const -> bool
    {
        return !(*this == other);
    }
};

struct Polygon
{
    std::vector<Point> vertices;
};

// Hash function for Point to use in unordered_map
struct PointHash
{
    auto operator()(const Point &p) const -> std::size_t
    {
        std::size_t const h1 = std::hash<float>{}(p.x);
        std::size_t const h2 = std::hash<float>{}(p.y);
        std::size_t const h3 = std::hash<float>{}(p.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct NavMesh
{
    std::vector<Point> vertices;

    void addVertex(const Point &p)
    {
        vertices.push_back(p);
    }

    void removeVertex(const Point &p)
    {
        vertices.erase(std::remove(vertices.begin(), vertices.end(), p), vertices.end());
    }

    void clear()
    {
        vertices.clear();
    }
};

struct Node
{
    Point point;
    float gCost;
    float fCost;

    Node(Point point, float gCost, float fCost)
        : point(point), gCost(gCost), fCost(fCost) {}

    auto operator>(const Node &other) const -> bool
    {
        return fCost > other.fCost;
    }
};

auto heuristic(const Point &p1, const Point &p2) -> float;
auto lineOfSight(const Point &s, const Point &sPrime, const std::vector<Polygon> &polygons) -> bool;
auto thetaStar(NavMesh &mesh, const Point &start, const Point &goal, const std::vector<Polygon> &obstaclePolygons) -> std::vector<Point>;
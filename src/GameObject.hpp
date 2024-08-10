#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "raylib.h"

class GameObject
{
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    GameObject(float x, float y, float z)
        : position{x, y, z}, rotation{0.0f, 0.0f, 0.0f}, scale{1.0f, 1.0f, 1.0f} {}

    GameObject(Vector3 pos, Vector3 rot, Vector3 scl)
        : position{pos}, rotation{rot}, scale{scl} {}

    void setPosition(float x, float y, float z)
    {
        position = {x, y, z};
    }

    void setRotation(float x, float y, float z)
    {
        rotation = {x, y, z};
    }

    void setScale(float x, float y, float z)
    {
        scale = {x, y, z};
    }

    Vector3 getPosition() const
    {
        return position;
    }

    Vector3 getRotation() const
    {
        return rotation;
    }

    Vector3 getScale() const
    {
        return scale;
    }
};

#endif // GAMEOBJECT_HPP

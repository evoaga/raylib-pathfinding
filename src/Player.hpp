#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject {
public:
    float speed; // Speed property
    int health;  // Health property

    Player(float x, float y, float z, float spd = 3.0f, int hp = 100)
        : GameObject(x, y, z), speed{spd}, health{hp} {}

    Player(Vector3 pos, Vector3 rot, Vector3 scl, float spd = 3.0f, int hp = 100)
        : GameObject(pos, rot, scl), speed{spd}, health{hp} {}

    void setSpeed(float spd) {
        speed = spd;
    }

    float getSpeed() const {
        return speed;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    int getHealth() const {
        return health;
    }

    bool isAlive() const {
        return health > 0;
    }
};

#endif // PLAYER_HPP

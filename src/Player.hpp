#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include <chrono>

class Player : public GameObject
{
public:
    float speed;                                                  // Speed property
    int health;                                                   // Health property
    bool alive;                                                   // Alive status
    std::chrono::time_point<std::chrono::steady_clock> deathTime; // Time of death
    float respawnDelay;                                           // Delay before respawn in seconds

    Player(float x, float y, float z, float spd = 3.0f, int hp = 100, float respawnTime = 5.0f)
        : GameObject(x, y, z), speed{spd}, health{hp}, alive{true}, respawnDelay{respawnTime} {}

    Player(Vector3 pos, Vector3 rot, Vector3 scl, float spd = 3.0f, int hp = 100, float respawnTime = 5.0f)
        : GameObject(pos, rot, scl), speed{spd}, health{hp}, alive{true}, respawnDelay{respawnTime} {}

    void setSpeed(float spd)
    {
        speed = spd;
    }

    float getSpeed() const
    {
        return speed;
    }

    void takeDamage(int damage)
    {
        if (!alive)
            return;
        health -= damage;
        if (health <= 0)
        {
            health = 0;
            alive = false;
            deathTime = std::chrono::steady_clock::now();
        }
    }

    int getHealth() const
    {
        return health;
    }

    bool isAlive() const
    {
        return alive;
    }

    void respawn(Vector3 newPosition, int newHealth)
    {
        position = newPosition;
        health = newHealth;
        alive = true;
    }

    bool shouldRespawn() const
    {
        if (!alive)
        {
            auto currentTime = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - deathTime).count();
            return duration >= respawnDelay;
        }
        return false;
    }
};

#endif // PLAYER_HPP

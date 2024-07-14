#ifndef PLAYERFACTORY_HPP
#define PLAYERFACTORY_HPP

#include "Player.hpp"

class PlayerFactory {
public:
    static Player createPlayer(float x, float y, float z, float spd = 3.0f, int hp = 100) {
        return Player(x, y, z, spd, hp);
    }

    static Player createPlayer(Vector3 pos, Vector3 rot, Vector3 scl, float spd = 3.0f, int hp = 100) {
        return Player(pos, rot, scl, spd, hp);
    }
};

#endif // PLAYERFACTORY_HPP

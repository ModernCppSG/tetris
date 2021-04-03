#ifndef TETRIS_COLLISIONS_H
#define TETRIS_COLLISIONS_H
#include <algorithm>
#include <vector>
#include <array>

namespace CollisionSystem {
    using tetriminoVector = std::vector<std::array<int, 2>>;
    static const int boundariesStart = 0;
    static const int boundariesXEnd = 10;
    static const int boundariesYEnd = 20;

    bool isOutOfBounds(const tetriminoVector& vector) {
        return std::any_of(vector.begin(), vector.end(), [&](const std::array<int, 2>& item)
        {return !(boundariesStart <= item[0] && item[0] <= boundariesXEnd) ||
                !(boundariesStart <= item[1] && item[1] <= boundariesYEnd);});
    }

    bool isColliding(const tetriminoVector& vector, const tetriminoVector& occupiedPositions) {
        return std::any_of(vector.begin(), vector.end(), [&](const std::array<int, 2>& item)
        {return std::find(occupiedPositions.begin(), occupiedPositions.end(), item)
                != occupiedPositions.end();});
    }

    tetriminoVector collisionProjection(tetriminoVector shadowPosition, const tetriminoVector& occupiedPositions) {
        while (!isOutOfBounds(shadowPosition) && !isColliding(shadowPosition, occupiedPositions)) {
            for (auto& item : shadowPosition) {
                item[1] += 1;
            }
        }
        for (auto& item : shadowPosition) {
            item[1] -= 1;
        }
        return shadowPosition;
    }

}

#endif //TETRIS_COLLISIONS_H

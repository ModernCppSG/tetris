#ifndef TETRIS_COLLISIONS_H
#define TETRIS_COLLISIONS_H
#include <algorithm>
#include <vector>
#include <array>

class evalCollisions{
    using tetriminoVector = std::vector<std::array<int, 2>>;
    int boundariesStart = 0;
    int boundariesXEnd = 50;
    int boundariesYEnd = 10;
    tetriminoVector occupiedPositions = {{}};

public:
    void updateOccupiedPositions(const std::vector<std::array<int, 2>>& frozenPosition) {
        for (const auto& item : frozenPosition) {
            occupiedPositions.push_back(item);
        }
    }

    void removeLine(int lineHeight) {
        for (int item = 0; item != occupiedPositions.size(); item++) {
            if (occupiedPositions[item][1] == lineHeight) {
                occupiedPositions.erase(occupiedPositions.begin() + item);
                item--;
            }
        }
    }

    bool isOutOfBounds(const tetriminoVector& vector) const {
        for (const auto& item : vector) {
            if (boundariesStart <= item[0] && item[0] <= boundariesXEnd &&
                boundariesStart <= item[1] && item[1] <= boundariesYEnd) {
                continue;
            } else { return true; }
        }
        return false;
    };

    bool isColliding(const tetriminoVector& vector) {
        for (const auto& item : vector) {
            if (std::find(occupiedPositions.begin(), occupiedPositions.end(), item)
            != occupiedPositions.end()) {
                return true;
            } else {
                continue;
            }
        }
        return false;
    };

    tetriminoVector collisionProjection(tetriminoVector shadowPosition) {
        while (!isOutOfBounds(shadowPosition) && !isColliding(shadowPosition)) {
            for (auto& item : shadowPosition) {
                item[1] += 1;
            }
        }
        for (auto& item : shadowPosition) {
            item[1] -= 1;
        }
        return shadowPosition;
    }

};

#endif //TETRIS_COLLISIONS_H

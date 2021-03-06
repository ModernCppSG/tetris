#ifndef TETRIS_COLLISIONS_H
#define TETRIS_COLLISIONS_H
#include <algorithm>
#include <vector>
#include <array>
#include "CoordinateSystem.h"
#include "Tetrimino.h"

class evalCollisions : public CoordinateSystem, Tetrimino {
public:

    bool isOutOfBounds(const tetriminoVector& vector) const {
        return std::any_of(vector.begin(), vector.end(), [&](const std::array<int, 2>& item)
        {return !(boundariesStart <= item[0] && item[0] <= boundariesXEnd) ||
                !(boundariesStart <= item[1] && item[1] <= boundariesYEnd);});
    }

    bool isColliding(const tetriminoVector& vector) {
        return std::any_of(vector.begin(), vector.end(), [&](const std::array<int, 2>& item)
        {return std::find(occupiedPositions.begin(), occupiedPositions.end(), item)
                != occupiedPositions.end();});
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

    tetriminoVector setPosition(tetriminoVector position, int direction) {
        auto newPosition = updatePosition(position, direction); // simulate new position

        if (!isColliding(newPosition) && !isOutOfBounds(newPosition)) { // tetrimino didn't collide
            return newPosition;

        } else { // tetrimino collided
            if (direction == right || direction == left || direction == up)
            { return position;} // collided sideways, no movement will be done

            else if (direction == down) {

                updateOccupiedPositions(newPosition);
                auto pos = assembleTetriminoCoords(getNextTetrimino(), getNextTetriminoDirection());

                if (!isColliding(pos) && !isOutOfBounds(pos)) { // freeze tetrimino
                    for (int iterador = 0; iterador != newPosition.size(); iterador++) {
                        score++;
                    }
                    return pos;

                } else { // tetrimino spawned inside another
                    std::cout << "game over; score = " << score << std::endl;
                    exit(0);
                }
            }
        }
    }

    bool isRotationPossible(std::array<std::array<int, 4>, 2> array, int direction) {
        auto rotatedPosition = assembleTetriminoCoords(array, direction);
        if (!isColliding(rotatedPosition) && !isOutOfBounds(rotatedPosition)) {
            return true;
        }
        else { return false; }
    }

};

#endif //TETRIS_COLLISIONS_H

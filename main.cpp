#include <iostream>
#include <array>
#include <vector>
#include "Collisions.h"
#include "CoordinateSystem.h"

CoordinateSystem coord;
evalCollisions c;

// interpretation of horizontal tetrimino
std::array<std::array<int,4>, 2> tetri = {{{{1, 0, 0, 0}},
                                           {{1, 1, 1, 1}}}};

// interpretation of vertical tetrimino
//    std::array<std::array<int,4>, 2> tetri = {{{{
//                                                 1,
//                                                 0,
//                                                 0,
//                                                 0}},
//                                               {{
//                                                   1,
//                                                   1,
//                                                   1,
//                                                   1}}}};

std::ostream& operator<<(std::ostream& os, std::array<int, 2> a) {
    os << "{";
    for(const auto& e : a) {
        os << e << " ";
    }
    os << "}";

    return os;
}

std::vector<std::array<int, 2>> setPosition(int direction, std::vector<std::array<int, 2>> position) {
    auto newPosition = coord.updatePosition(direction, position);
    if (!c.isColliding(newPosition) && !c.isOutOfBounds(newPosition)) {

        // if not colliding with another tetrimino or with the walls, new position will be set
        std::cout << "position is OK and was set" << std::endl;
        std::cout << "tetrimino position: ";
        for(const auto& e : newPosition) {
            std::cout << e;
        }
        std::cout << std::endl;

        // if a new position was set, the collision projection must be recalculated
        auto a = c.collisionProjection(newPosition);
        std::cout << "shadow position: ";
        for(const auto& e : a) {
            std::cout << e;
        }
        return newPosition;
    } else {
        std::cout << "collision happened";
        if (direction == 0 || direction == 1) {

            // tetrimino moved sideways and collided, new position won't be set
            std::cout << ", tetrimino not moved" << std::endl;
            return position;
        } else if (direction == 2) {

            // tetrimino moved down and collided, must be frozen
            std::cout << ", tetrimino frozen. Making new tetrimino" << std::endl;
            c.updateOccupiedPositions(newPosition);
            return coord.assembleTetriminoPosArray(tetri, 0);
        }
    }
}

int main() {
    // assemble coordinates array for each pixel (hitboxes), making collision possible. 0 = vertical and 1 = horizontal
    auto position = coord.assembleTetriminoPosArray(tetri, 0);
    std::cout << "tetrimino position: ";
    for(const auto& e : position) {
        std::cout << e;
    }
    std::cout << std::endl;

    // move tetrimino to the right
    int direction;
    while (true) {
        std::cout << "\nnext position: ";
        std::cin >> direction;
        position = setPosition(direction, position);
    }

    return 0;
};

#include <iostream>
#include <array>
#include <vector>
#include "Collisions.h"
#include "CoordinateSystem.h"

CoordinateSystem coord;
evalCollisions c;

std::ostream& operator<<(std::ostream& os, std::array<int, 2> a) {
    os << "{";
    for(const auto& e : a) {
        os << e << " ";
    }
    os << "}";

    return os;
}

void setPosition(int direction, std::vector<std::array<int, 2>> position) {
    auto newPosition = coord.updatePosition(0, std::move(position));
    if (!c.isColliding(newPosition) && !c.isOutOfBounds(newPosition)) {

        // if not colliding with another tetrimino or with the walls, new position will be set
        std::cout << "position is OK and was set" << std::endl;

        // if a new position was set, the collision projection must be recalculated
        auto a = c.collisionProjection(newPosition);
        std::cout << "shadow position: ";
        for(const auto& e : a) {
            std::cout << e;
        }
    } else {
        std::cout << "collision happened";
        if (direction == 0 || direction == 1) {

            // tetrimino moved sideways and collided, new position won't be set
            std::cout << ", tetrimino not moved" << std::endl;
        }
        else if (direction == 3){

            // tetrimino moved down and collided, must be frozen
            std::cout << ", tetrimino frozen" << std::endl;
            c.updateOccupiedPositions(newPosition);
        }
    }
}

int main() {
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


    // assemble coordinates array for each pixel (hitboxes), making collision possible. 0 = vertical and 1 = horizontal
    auto position = coord.assembleTetriminoPosArray(tetri, 0);
    std::cout << "tetri position: ";
    for(const auto& e : position) {
        std::cout << e;
    }
    std::cout << std::endl;

    // move tetrimino to the right
    setPosition(0, position);

    return 0;
};

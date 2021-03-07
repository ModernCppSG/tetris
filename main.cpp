#include <iostream>
#include <array>
#include "Collisions.h"

evalCollisions c;

int score = 0;

std::array<std::array<int,4>, 2> tetri = {{{{1, 0, 0, 0}},
                                           {{1, 1, 1, 1}}}};

std::ostream& operator<<(std::ostream& os, std::array<int, 2> a) {
    os << "{";
    for(const auto& e : a) {
        os << e << " ";
    }
    os << "}";

    return os;
}

int main() {
    auto position = c.assembleTetriminoCoords(tetri, 0, false);

    int direction;
    while (true) {
        std::cout << "\nnext position: ";
        std::cin >> direction;
        if (direction > 3 || direction < 0) {
            break;
        }
        position = c.setPosition(position, direction);
        for(const auto& e : position) {
            std::cout << e;
        }
        std::cout << std::endl;
    }

    return 0;
};

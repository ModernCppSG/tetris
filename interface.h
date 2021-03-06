#ifndef TETRIS_INTERFACE_H
#define TETRIS_INTERFACE_H

#include <iostream>
#include <cstdio>
#include <string>

class Size {
public:
    Size(int width, int height): width_{width}, height_{height} {}
    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_;
    int height_;
};

void prepInterface() {
    std::cout << "\033[2J";
}

void refCursor(const std::string& x, const std::string& y) {
    std::cout << "\033[H" << "\033[" + x + "C" << "\033[" + y + "B";
}

void printWalls(const Size& walls) {
    std::cout << "\u2554";
    for (int i = 0; i < walls.width(); ++i) {
        std::cout << "\u2550";
    }
    std::cout << "\u2557";

    for (int i = 0; i < walls.height(); ++i) {
        std::cout << "\033[1B" << "\033[" + std::to_string(walls.width() + 2) + "D";
        std::cout << "\u2551" << "\033[" + std::to_string(walls.width()) + "C" << "\u2551";
    }

    std::cout << "\033[1B" << "\033[" + std::to_string(walls.width() + 2) + "D";
    std::cout << "\u255A";
    for (int i = 0; i < walls.width(); ++i) {
        std::cout << "\u2550";
    }
    std::cout << "\u255D";
}

#endif //TETRIS_INTERFACE_H

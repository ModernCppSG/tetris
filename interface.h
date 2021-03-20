#ifndef TETRIS_INTERFACE_H
#define TETRIS_INTERFACE_H

#include <iostream>
#include <cstdio>
#include <string>

//each \033[ is an ANSI escape sequence
//class Size is used to define the dimensions of all walls in the game interface
class Size {
public:
    Size(int width, int height): width_{width}, height_{height} {}
    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_;
    int height_;
};

//prepInterface clears the terminal
void prepInterface() {
    std::cout << "\033[2J";
}

//refCursor positions the cursor at any coordinate of the terminal
void refCursor(const std::string& x, const std::string& y) {
    std::cout << "\033[H"; //positions the cursor at the origin
    std::cout << "\033[" + x + "C"; //positions the cursor at the x-column
    std::cout << "\033[" + y + "B"; //positions the cursor at the y-line
}

//printWalls uses the Size as an input for printing the walls at the current cursor position line by line
//each \u25?? is a different ASCII symbol used in the wall
void printWalls(const Size& walls) {
    //beggin by printing the first line of the wall
    std::cout << "\u2554";
    for (int i = 0; i < walls.width(); ++i) {
        std::cout << "\u2550";
    }
    std::cout << "\u2557";

    //print, line by line, the walls that are in the middle
    for (int i = 0; i < walls.height(); ++i) {
        std::cout << "\033[1B" << "\033[" + std::to_string(walls.width() + 2) + "D"; //repositioning of the cursor to be underneath of the above line
        std::cout << "\u2551" << "\033[" + std::to_string(walls.width()) + "C" << "\u2551";
    }

    //print the last line of the wall
    std::cout << "\033[1B" << "\033[" + std::to_string(walls.width() + 2) + "D";
    std::cout << "\u255A";
    for (int i = 0; i < walls.width(); ++i) {
        std::cout << "\u2550";
    }
    std::cout << "\u255D";

}

void moveLeft();

void clearPosition() {
    std::cout << " ";
    moveLeft();
}

void setPosition() {
    std::cout << "#";
    moveLeft();
}

void moveUp() {
    std::cout << "\033[1A";
}

void moveDown() {
    std::cout << "\033[1B";
}

void moveRight() {
    std::cout << "\033[1C";
}

void moveLeft() {
    std::cout << "\033[1D";
}

void printCerquilha(int xOld, int yOld, int x, int y) {
    std::cout << "\033[0;0f";
    std::cout << "   x: " << x << "\t   y: " << y << std::endl;
    std::cout << "xOld: " << xOld << "\tyOld: " << yOld;
    std::cout << "\033[" + std::to_string(yOld) << ";" << std::to_string(xOld) << "f";
    std::cout << "o";
    std::cout << "\033[" + std::to_string(y) << ";" << std::to_string(x) << "f";
    std::cout << "#";
}

#endif //TETRIS_INTERFACE_H

#include "interface.h"

int main() {
    prepInterface();

    refCursor("5", "3");
    Size screen = {15, 20};
    printWalls(screen);

    refCursor("25", "3");
    Size points = {10, 3};
    printWalls(points);

    refCursor("25", "9");
    Size piece = {10, 3};
    printWalls(piece);


    return 0;
}
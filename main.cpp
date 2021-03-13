#include "interface.h"

int main() {
    prepInterface(); //clears the terminal

    refCursor("5", "3"); //positions the cursor at the 5-column and 3-line
    Size screen = {15, 20}; //size of the "screen" (intended here to be the playable zone) is 15 units of width and 20 units of height
    printWalls(screen);

    refCursor("25", "3");
    Size points = {10, 3};
    printWalls(points);

    refCursor("25", "9");
    Size piece = {10, 3};
    printWalls(piece);


    return 0;
}
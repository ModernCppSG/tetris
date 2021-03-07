#ifndef TETRIS_COORDINATESYSTEM_H
#define TETRIS_COORDINATESYSTEM_H
#include <vector>
#include <array>

class CoordinateSystem {
protected:
    using tetriminoVector = std::vector<std::array<int, 2>>;
    static const int boundariesStart = 0;
    static const int boundariesXEnd = 10;
    static const int boundariesYEnd = 20;
    tetriminoVector occupiedPositions = {{}};

    enum Movements {
        right = 0,
        left = 1,
        down = 2,
        up = 3
    };

private:
    tetriminoVector tetriminoPosVector;
    std::array<std::array<int, 2>, 8> horizontalPos;
    std::array<std::array<int, 2>, 8> verticalPos;

    static const int defaultPosX = 8;
    static const int defaultPosY = 0;
    int currentPosX = 0;
    int currentPosY = 0;

    std::array<std::array<int, 2>, 8> makeHorizontalArray (int PosX, int PosY) {
        horizontalPos = {{
            {{PosX, PosY}},
            {{PosX + 1, PosY}},
            {{PosX + 2, PosY}},
            {{PosX + 3, PosY}},
            {{PosX, PosY + 1}},
            {{PosX + 1, PosY + 1}},
            {{PosX + 2, PosY + 1}},
            {{PosX + 3, PosY + 1}}
        }};
        return horizontalPos;
    }
    std::array<std::array<int, 2>, 8> makeVerticalArray (int PosX, int PosY) {
        verticalPos = {{
            {{PosX + 1, PosY}},
            {{PosX + 1, PosY + 1}},
            {{PosX + 1, PosY + 2}},
            {{PosX + 1, PosY + 3}},
            {{PosX + 2, PosY}},
            {{PosX + 2, PosY + 1}},
            {{PosX + 2, PosY + 2}},
            {{PosX + 2, PosY + 3}}
        }};
        return verticalPos;
    }

    std::array<std::array<int, 2>, 8> determineWhichDirection(int direction, bool isRotating) {
        if (isRotating) {
            currentPosX = defaultPosX;
            currentPosY = defaultPosY;
        }
        if (direction == 0) {
            if (!isRotating) {
                return (makeVerticalArray(defaultPosX, defaultPosY));
            } else {
                return (makeVerticalArray(currentPosX, currentPosY));
            }
        } else {
            if (!isRotating) {
                return (makeHorizontalArray(defaultPosX, defaultPosY));
            } else {
                return (makeHorizontalArray(currentPosX, currentPosY));
            }
        }
    }

public:
    int score = 0;

    // assemble coordinates array for each pixel (hitboxes), making collision possible. 0 = vertical and 1 = horizontal
    tetriminoVector assembleTetriminoCoords(std::array<std::array<int, 4>, 2> array, int direction, bool isRotating) {
        tetriminoPosVector.clear();
        int index = 0;
        int member = 0;
        auto posArray = determineWhichDirection(direction, isRotating);
        for (const auto& item : posArray) {
            if (array[index][member]) {
                tetriminoPosVector.push_back(item);
            }
            member++;
            if (member == 4) {
                member = 0;
                index = 1;
            }
        }
        return tetriminoPosVector;
    }

    tetriminoVector updatePosition(tetriminoVector vector, int direction) {
        std::array<int, 2> sum{};
        switch (direction) {
            case right:
                sum = {{1, 0}};
                currentPosX++;
                break;
            case left:
                sum = {{-1, 0}};
                currentPosX--;
                break;
            case down:
                sum = {{0, 1}};
                currentPosY++;
                break;
            case up:
                sum = {{0, -1}};
                currentPosY--;
                break;
            default:
                sum = {{0, 0}};
                break;
        }
        for (auto& item : vector) {
            item[0] += sum[0];
            item[1] += sum[1];
        }
        return vector;
    }

    void updateOccupiedPositions(const tetriminoVector& frozenPosition) {
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

};

#endif //TETRIS_COORDINATESYSTEM_H

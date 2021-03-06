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

    static const int defaultPosX = 8;
    static const int defaultPosY = 0;

    std::array<std::array<int, 2>, 8> horizontalPos = {{
        {{defaultPosX, defaultPosY}},
        {{defaultPosX + 1, defaultPosY}},
        {{defaultPosX + 2, defaultPosY}},
        {{defaultPosX + 3, defaultPosY}},
        {{defaultPosX, defaultPosY + 1}},
        {{defaultPosX + 1, defaultPosY + 1}},
        {{defaultPosX + 2, defaultPosY + 1}},
        {{defaultPosX + 3, defaultPosY + 1}}
    }};

    std::array<std::array<int, 2>, 8> verticalPos = {{
       {{defaultPosX + 1, defaultPosY}},
       {{defaultPosX + 1, defaultPosY + 1}},
       {{defaultPosX + 1, defaultPosY + 2}},
       {{defaultPosX + 1, defaultPosY + 3}},
       {{defaultPosX + 2, defaultPosY}},
       {{defaultPosX + 2, defaultPosY + 1}},
       {{defaultPosX + 2, defaultPosY + 2}},
       {{defaultPosX + 2, defaultPosY + 3}}
    }};

    std::array<std::array<int, 2>, 8> determineWhichDirection(int direction) {
        if (direction == 0) {
            return (verticalPos);
        } else {
            return (horizontalPos);
        }
    }

public:
    int score = 0;

    // assemble coordinates array for each pixel (hitboxes), making collision possible. 0 = vertical and 1 = horizontal
    tetriminoVector assembleTetriminoCoords(std::array<std::array<int, 4>, 2> array, int direction) {
        tetriminoPosVector.clear();
        int index = 0;
        int member = 0;
        auto posArray = determineWhichDirection(direction);
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

    static tetriminoVector updatePosition(tetriminoVector vector, int direction) {
        std::array<int, 2> sum{};
        switch (direction) {
            case right:
                sum = {{1, 0}};
                break;
            case left:
                sum = {{-1, 0}};
                break;
            case down:
                sum = {{0, 1}};
                break;
            case up:
                sum = {{0, -1}};
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

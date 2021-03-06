#ifndef TETRIS_TETRIMINO_H
#define TETRIS_TETRIMINO_H

class Tetrimino {
    std::array<std::array<int,4>, 2> tetri = {{{{1, 0, 0, 0}},
                                               {{1, 1, 1, 1}}}};

public:
    std::array<std::array<int, 4>, 2> getNextTetrimino () {
        return  tetri;
    }

   int getNextTetriminoDirection () {
        return 0;
    }
};

#endif //TETRIS_TETRIMINO_H

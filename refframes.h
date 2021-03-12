// Copyright (c) 2021 ModernCppSG
// Definition of local, global and printing reference frames
// Created by Caju on 2021-03-07
//

#ifndef CODE_TETRIS_REFFRAMES_H_
#define CODE_TETRIS_REFFRAMES_H_

#include <array>

//   X Y
// [[1 0]
//  [0 1]]
using matrix = std::array<std::array<float, 2>, 2>;  // 2D Cartesian

struct ReferenceFrame {
  struct position {
    float x, y;
  } origin;
  matrix orientation;
  ReferenceFrame(float x, float y) {
    origin.x = x;
    origin.y = y;
  }
  void translate(float x, float y) {
    origin.x += x;
    origin.y += y;
  }

  void rotate(char direction) {
    matrix rotation;
    if (direction == 'L') {
      rotation = {{{0, -1}, {1, 0}}};  // anti-clockwise rotation
    } else if (direction == 'R') {
      rotation = {{{0, 1}, {-1, 0}}};  // clockwise rotation
    } else {
    }
    orientation = multiply(rotation, orientation);
  }

 private:
  // Implements naive matrix multiplication
  matrix multiply(matrix A, matrix B) {
    matrix C;
    int i, j, k;
    float sum;
    for (i = 0; i < 2; ++i) {
      for (j = 0; j < 2; ++j) {
        sum = 0;
        for (k = 0; k < 2; ++k) {
          sum += A[i][k] * B[k][j];
        }
        C[i][j] = sum;
      }
    }
    return C;
  }
};

ReferenceFrame local(5, 21);  // Block starts at MIDLE-TOP of playing field
ReferenceFrame GLOBAL(0, 0);
ReferenceFrame PRINTING(0, 20);  // TODO(aocci): flip the printing Frame down

#endif  // CODE_TETRIS_REFFRAMES_H_

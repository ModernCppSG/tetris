// Copyright (c) 2021 ModernCppSG
// General Tetriminos class and its ramifications
// Created by Caju on 2021-02-27

#ifndef CODE_TETRIS_TETRIMINOS_H_
#define CODE_TETRIS_TETRIMINOS_H_

#include <array>
#include <iostream>
#include <string>
#include <tuple>

#include "./refframes.h"

struct Pixel {
  int x, y;    // index position of pixel inside the 2 by 4 envelope
  bool state;  // if pixel is lit or not
};

struct Color {
  std::string name;
  std::string HEXCODE;
};

using envelope = std::array<std::array<bool, 4>, 2>;  // is a matrix

class Tetrimino {
 public:
  ReferenceFrame origin;  // reference frame placed at bottom-left pixel
  envelope pixels;        // is the standard cell-matrix that defines the block
  Color color;

 protected:
  std::tuple<int, int> rotation_point;  // index (a, b) for the cell around
                                        // which the rotation happens
  void display(envelope block) {
    // Print block `drawing` to terminal using `*` and `#` for debugging
    // Tetrimino() = {};
    std::cout << "Block structure:\n";
    for (int i; i < 2; i++) {
      std::array row = block[i];
      for (bool pixel : row) {
        if (pixel == true)
          std::cout << "#";
        else
          std::cout << ".";
      }
    }
  }
  virtual void initialize() = 0;
  virtual void rotate() = 0;
};

class Ohh : public Tetrimino {
  // NOTE square should not rotate
 public:
  bool envelope[2][4] = {{1, 1, 0, 0},
                         {1, 1, 0, 0}};  // initialize cell-matrix for square
};

class Iye : public Tetrimino {
 public:
  bool envelope[2][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}};
};

class Tee : public Tetrimino {
  bool envelope[2][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}};
};

// Non-Symmetric pieces are further specialized into their left and right
// versions
class Ehl : public Tetrimino {
  bool envelope[2][4] = {{1, 0, 0, 0}, {1, 1, 1, 0}};
};

class Jay : public Tetrimino {
  bool envelope[2][4] = {{0, 0, 0, 1}, {0, 1, 1, 1}};
};

class Ass : public Tetrimino {
  bool envelope[2][4] = {{0, 1, 1, 0}, {1, 1, 0, 0}};
};

class Zee : public Tetrimino {
  bool envelope[2][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}};
};

#endif  // CODE_TETRIS_TETRIMINOS_H_
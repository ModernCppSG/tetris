// Copyright (c) 2021 ModernCppSG
// General Tetriminos class and its ramifications
// Created by Caju on 2021-02-27
//

#ifndef CODE_TETRIS_TETRIMINOS_H_
#define CODE_TETRIS_TETRIMINOS_H_

#include <array>
#include <iostream>
#include <string>
#include <tuple>

struct Pixel {
  int x, y;    // index position of pixel inside the 2 by 4 envelope
  bool state;  // if pixel is lit or not
};

struct Color {
  std::string name;
  std::string HEXCODE;
};

using envelope = std::array<std::array<bool, 4>, 2>;

class Tetrimino {
 public:
  std::string color;
  Pixel coordinate;
  Pixel orientation;  // TODO(aocci) : implement orientation/frame of reference
  int numberOfSquares =
      4;  // maximum number of filled-in squares any piece can have
  std::tuple<int, int> rotation_point;  // index (a, b) for the cell around
                                        // which the rotation happens
  bool cellMatrix;  // is the more general cell-matrix accounting for rotations
  envelope pixels;  // is the standard cell-matrix that defines the block

 private:
  // Print block `drawing` to terminal using `*` and `#` for debugging
  // Tetrimino() = {};
  void display() { std::cout << "Block structure"; }
  virtual void initialize() = 0;
  virtual void rotate() = 0;
};

// Divide Blocks into two main families:
//  * Symmetric Pieces, e.g., T, Square, I
//  * Non-Symmetric Pieces: L and Z
class SymmetricTet : public Tetrimino {};

class Ohh : public SymmetricTet {
  // NOTE square should not rotate
 public:
  bool envelope[2][4] = {{1, 1, 0, 0},
                         {1, 1, 0, 0}};  // initialize cell-matrix for square
  void display() {
    for (bool pixel : envelope) {
      if (pixel == true)
        std::cout << "#";
      else
        std::cout << "*";
    }
  }
};

class Iye : public SymmetricTet {};

class Tee : public SymmetricTet {};

class NonSymmetricTet : private Tetrimino {};

// Non-Symmetric pieces are further specialized into their left and right
// versions
class Ehl : public NonSymmetricTet {};

class Jay : public NonSymmetricTet {};

class Ass : public NonSymmetricTet {};

class Zee : public NonSymmetricTet {};

#endif  // CODE_TETRIS_TETRIMINOS_H_

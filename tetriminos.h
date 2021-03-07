// General Tetriminos class and its ramifications
// Created by Caju on 2021-02-27
//

#ifndef TETRIMINOS_H
#define TETRIMINOS_H

#include <iostream>
#include <array>

struct Pixel {
  int x, y;   // index position of pixel inside the 2 by 4 envelope
  bool state; // if pixel is lit or not
};

using envelope = std::array<std::array<bool, 4>, 2>;

class Tetrimino {
public:
  Pixel coordinate;
  Pixel orientation; // TODO
  int numberOfSquares =
      4; // maximum number of filled-in squares any piece can have
  std::tuple<int, int> rotation_point; // index (a, b) for the cell around which
                                       // the rotation happens
  bool cellMatrix; // is the more general cell-matrix accounting for rotations
  envelope tetrimino;   // is the standard cell-matrix that defines the block

private:
  // Print block `drawing` to terminal using `*` and `#` for debugging
  void display() { std::cout << "Block structure"; };
  virtual void initialize() = 0;
  virtual void rotate() = 0;
};

// Divide Blocks into two main families:
//  * Symmetric Pieces, e.g., T, Square, I
//  * Non-Symmetric Pieces: L and Z
class SymmetricTet : public Tetrimino {};

class Square : public SymmetricTet {
  // NOTE square should not rotate
public:
  bool envelope[2][4] = {{1, 1, 0, 0},
                         {1, 1, 0, 0}}; // initialize cell-matrix for square
  void display() {
    for (bool pixel : envelope) {
      if (pixel == true)
        std::cout << "#";
      else
        std::cout << "*";
    };
  };
};

class Line : public SymmetricTet {};

class Tee : public SymmetricTet {};

class NonSymmetricTet : private Tetrimino {};

class Ls : private NonSymmetricTet {};

class Zs : private NonSymmetricTet {};

// Non-Symmetric pieces are further specialized into their left and right
// versions
class LeftL : public Ls {};

class RightL : public Ls {};

class LeftZ : public Ls {};

class RightZ : public Ls {};

#endif // TETRIMINOS_H

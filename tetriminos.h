// General Tetriminos class and its ramifications
// Created by Caju on 2021-02-27
//

#include <iostream>

class Tetrimino {
public:
  int numberOfBlocks = 4;
  // Print block `drawing` to terminal using `*` for debugging
  void display() { std::cout << "Block structure"; };
};

// Divide Blocks into two main families:
//  * Symmetric Pieces, e.g., T, Square, I
//  * Non-Symmetric Pieces: L and Z
class SymmetricTet : private Tetrimino {};

class Square : public SymmetricTet {};

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

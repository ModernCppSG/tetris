// Definition of local, global and printing reference frames
// Created by Caju on 2021-03-07
//

#ifndef REFFRAMES_H
#define REFFRAMES_H

#include <array>

struct ReferenceFrame {};

struct Local : ReferenceFrame {};
struct Global : ReferenceFrame {};
struct Printing : ReferenceFrame {};

class Rotation {
public:
  std::array<std::array<float, 2>, 2> matrix; // 2D rotation matrix
};
class CW : Rotation {};  // Clock-wise rotation of 90 degrees
class CCW : Rotation {}; // Counter Clock-wise rotation of 90 degrees

#endif // REFFRAMES_H

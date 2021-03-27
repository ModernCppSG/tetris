// Copyright (c) 2021 ModernCppSG
// Testing procedures for refframes.h module
// Created by Caju on 2021-03-07

#include <array>

#include "../refframes.h"
#include "./gtest/gtest.h"

std::array<std::array<float, 2>, 2> IDENTITY = {{{1, 0}, {0, 1}}};

ReferenceFrame test(0, 0);
TEST(TestReferenceFrames, CounterClockwiseRotation) {
  matrix rot090 = {{{0, -1}, {1, 0}}};
  matrix rot180 = {{{-1, 0}, {0, -1}}};
  matrix rot270 = {{{0, 1}, {-1, 0}}};
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot090);
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot180);
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot270);
  test.rotate('L');
  ASSERT_EQ(test.orientation, IDENTITY);
}
// Rotate right (counter clockwise)
//
//
// Rotate left, then right
//
// Rotate right then left
//
//
// Rotate left 4 times should return to the starting condition.
// In other words: 90 + 90 + 90 +90 = 360 degree rotation which is identic to
// 0 degree "rotation".
//
// Rotate right 4 times should return to the starting condition.
// In other words: -90 - 90 - 90 - 90 = -360 degree rotation which is identic to
// 0 degree "rotation".

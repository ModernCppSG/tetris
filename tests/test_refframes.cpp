// Copyright (c) 2021 ModernCppSG
// Testing procedures for refframes.h module
// Created by Caju on 2021-03-07

#include <array>

#include "../refframes.h"
#include "./gtest/gtest.h"

std::array<std::array<float, 2>, 2> IDENTITY = {{{1, 0}, {0, 1}}};

// Rotate left (counter clockwise)
ReferenceFrame test(0, 0);
TEST(TestReferenceFrames, CounterClockwiseRotation) {
  matrix rot090 = {{{0, -1}, {1, 0}}};
  matrix rot180 = {{{-1, 0}, {0, -1}}};
  matrix rot270 = {{{0, 1}, {-1, 0}}};
  // Reference frame should be initialized as identity
  ASSERT_EQ(test.orientation, IDENTITY);
  // Rotate then compare
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot090);
  // Repeat three times
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot180);
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot270);
  test.rotate('L');
  // Finally, the refframe should have gone back to the initial state
  ASSERT_EQ(test.orientation, IDENTITY);
}

// Rotate right (clockwise)
TEST(TestReferenceFrames, ClockwiseRotation) {
  matrix minus_rot090 = {{{0, 1}, {-1, 0}}};
  matrix minus_rot180 = {{{-1, 0}, {0, -1}}};
  matrix minus_rot270 = {{{0, -1}, {1, 0}}};
  // Reference frame should be initialized as identity
  ASSERT_EQ(test.orientation, IDENTITY);
  // Rotate then compare
  test.rotate('R');
  ASSERT_EQ(test.orientation, minus_rot090);
  // Repeat three times
  test.rotate('R');
  ASSERT_EQ(test.orientation, minus_rot180);
  test.rotate('R');
  ASSERT_EQ(test.orientation, minus_rot270);
  test.rotate('R');
  // Finally, the refframe should have gone back to the initial state
  ASSERT_EQ(test.orientation, IDENTITY);
}
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

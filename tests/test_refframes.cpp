// Copyright (c) 2021 ModernCppSG
// Testing procedures for refframes.h module
// Created by Caju on 2021-03-07

#include <array>
#include <iostream>

#include "../refframes.h"
#include "./gtest/gtest.h"

std::array<std::array<int, 2>, 2> IDENTITY = {{{1, 0}, {0, 1}}};

matrix rot090 = {{{0, -1}, {1, 0}}};
matrix rot180 = {{{-1, 0}, {0, -1}}};
matrix rot270 = {{{0, 1}, {-1, 0}}};

matrix minus_rot090 = {{{0, 1}, {-1, 0}}};
matrix minus_rot180 = {{{-1, 0}, {0, -1}}};
matrix minus_rot270 = {{{0, -1}, {1, 0}}};

// Rotate left (counter clockwise)
TEST(TestReferenceFrames, CounterClockwiseRotation) {
  ReferenceFrame test(0, 0);
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
  ReferenceFrame test(0, 0);
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

TEST(TestReferenceFrames, MixedRotations) {
  // Rotate left, then right
  ReferenceFrame testL(0, 0);
  testL.rotate('L');
  testL.rotate('R');
  ASSERT_EQ(testL.orientation, IDENTITY);

  testL.rotate('L');
  testL.rotate('L');
  testL.rotate('R');
  ASSERT_EQ(testL.orientation, rot090);

  // Rotate right, then left
  ReferenceFrame testR(0, 0);
  testR.rotate('R');
  testR.rotate('L');
  ASSERT_EQ(testR.orientation, IDENTITY);

  testR.rotate('R');
  testR.rotate('R');
  testR.rotate('L');
  ASSERT_EQ(testR.orientation, minus_rot090);
}

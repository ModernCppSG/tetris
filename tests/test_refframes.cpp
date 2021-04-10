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
TEST(CounterClockWise, Initialization) {
  ReferenceFrame test(0, 0);
  // Reference frame should be initialized as identity
  ASSERT_EQ(test.orientation, IDENTITY);
}

TEST(CounterClockWise, SingleRotation) {
  ReferenceFrame test(0, 0);
  // Rotate then compare
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot090);
}
TEST(CounterClockWise, DoubleRotation) {
  ReferenceFrame test(0, 0);
  test.rotate('L');
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot180);
}
TEST(CounterClockWise, TripleRotation) {
  ReferenceFrame test(0, 0);
  test.rotate('L');
  test.rotate('L');
  test.rotate('L');
  ASSERT_EQ(test.orientation, rot270);
}
TEST(CounterClockWise, QuadrupleRotation) {
  ReferenceFrame test(0, 0);
  test.rotate('L');
  test.rotate('L');
  test.rotate('L');
  test.rotate('L');
  // Finally, the refframe should have gone back to the initial state
  ASSERT_EQ(test.orientation, IDENTITY);
}

// Rotate right (clockwise)
TEST(ClockWise, SingleRotation) {
  ReferenceFrame test(0, 0);
  // Rotate then compare
  test.rotate('R');
  ASSERT_EQ(test.orientation, minus_rot090);
}
TEST(ClockWise, DoubleRotation) {
  ReferenceFrame test(0, 0);
  test.rotate('R');
  test.rotate('R');
  ASSERT_EQ(test.orientation, minus_rot180);
}
TEST(ClockWise, TripleRotation) {
  ReferenceFrame test(0, 0);
  test.rotate('R');
  test.rotate('R');
  test.rotate('R');
  ASSERT_EQ(test.orientation, minus_rot270);
}
TEST(ClockWise, QuadrupleRotation) {
  ReferenceFrame test(0, 0);
  test.rotate('R');
  test.rotate('R');
  test.rotate('R');
  test.rotate('R');
  // Finally, the refframe should have gone back to the initial state
  ASSERT_EQ(test.orientation, IDENTITY);
}

TEST(MixedRotations, LeftRight) {
  ReferenceFrame testL(0, 0);
  testL.rotate('L');
  testL.rotate('R');
  ASSERT_EQ(testL.orientation, IDENTITY);
}

TEST(MixedRotations, LeftLeftRight) {
  ReferenceFrame testL(0, 0);
  testL.rotate('L');
  testL.rotate('L');
  testL.rotate('R');
  ASSERT_EQ(testL.orientation, rot090);
}

TEST(MixedRotations, RightLeft) {
  ReferenceFrame testR(0, 0);
  testR.rotate('R');
  testR.rotate('L');
  ASSERT_EQ(testR.orientation, IDENTITY);
}

TEST(MixedRotations, RightRightLeft) {
  ReferenceFrame testR(0, 0);
  testR.rotate('R');
  testR.rotate('R');
  testR.rotate('L');
  ASSERT_EQ(testR.orientation, minus_rot090);
}

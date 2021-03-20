// Copyright (c) 2021 ModernCppSG
// Testing procedures for refframes.h module
// Created by Caju on 2021-03-07
//

// Rotate left (clockwise)
//
// Rotate right (counter clockwise)
//
//
// Rotate left, then right
//
// Rotate right then left
//
//
#include "./gtest/gtest.h"
#include "./refframes.h"
// Rotate left 4 times should return to the starting condition.
// In other words: 90 + 90 + 90 +90 = 360 degree rotation which is identic to
// 0 degree "rotation".
//
// Rotate right 4 times should return to the starting condition.
// In other words: -90 - 90 - 90 - 90 = -360 degree rotation which is identic to
// 0 degree "rotation".

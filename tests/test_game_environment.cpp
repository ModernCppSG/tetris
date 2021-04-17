//
// Created by grilo on 10/04/2021.
//

#include "../interface.h"
#include <gtest/gtest.h>
#include <array>

constexpr std::array<int, 10> sizes  = {10, 20, 30, 0, -2, -1, -80, 1000, INT32_MAX, INT32_MIN};

// Testing zero
TEST(ClassSize, SizeZero) {
    //Size testSize{}; //not allowed: compilation error

    Size testSize{0, 0};

    Size testSize{0, 0};
    ASSERT_EQ(testSize.height(), 0);
    ASSERT_EQ(testSize.width(), 0);
}

// Testing positive numbers
TEST(ClassSize, PositiveIntegersSizes) {

    Size testSize{0, 0};

    testSize = Size{10, 10};
    ASSERT_EQ(testSize.width(), 10);
    ASSERT_EQ(testSize.height(), 10);

    testSize = Size{15, 25};
    ASSERT_EQ(testSize.width(), 15);
    ASSERT_EQ(testSize.height(), 25);

    testSize = Size{15, 0};
    ASSERT_EQ(testSize.width(), 15);
    ASSERT_EQ(testSize.height(), 0);
}

// Testing negative numbers
TEST(ClassSize, NegativeIntegersSizes) {

    Size testSize{0, 0};

    testSize = Size{-10, -10};
    ASSERT_EQ(testSize.width(), 10);
    ASSERT_EQ(testSize.height(), 10);

    testSize = Size{-15, -25};
    ASSERT_EQ(testSize.width(), 15);
    ASSERT_EQ(testSize.height(), 25);
}

// Testing zero, positive and negative numbers
TEST(ClassSize, MixedPositiveNegativeIntegersSizes) {

    Size testSize{0, 0};
    
    testSize = Size{-10, 10};
    ASSERT_EQ(testSize.width(), 10);
    ASSERT_EQ(testSize.height(), 10);
    
    testSize = Size{15, -25};
    ASSERT_EQ(testSize.width(), 15);
    ASSERT_EQ(testSize.height(), 25);
    
    testSize = Size{-15, 0};
    ASSERT_EQ(testSize.width(), 15);
    ASSERT_EQ(testSize.height(), 0);
    
    testSize = Size{0, -42};
    ASSERT_EQ(testSize.width(), 0);
    ASSERT_EQ(testSize.height(), 42);
}

// Testing with extreme integers (maximum and minimum)
TEST(ClassSize, ExtremeIntegersSizes) {

    Size testSize{0, 0};

    testSize = Size{-10, INT32_MAX};
    ASSERT_EQ(testSize.width(), 10);
    ASSERT_EQ(testSize.height(), INT32_MAX);
    
    testSize = Size{INT32_MIN, -25};
    ASSERT_EQ(testSize.width(), INT32_MIN);
    ASSERT_EQ(testSize.height(), 25);
    
    testSize = Size{INT32_MAX, INT32_MAX};
    ASSERT_EQ(testSize.width(), INT32_MAX);
    ASSERT_EQ(testSize.height(), INT32_MAX);
    
    testSize = Size{INT32_MAX, INT32_MIN};
    ASSERT_EQ(testSize.width(), INT32_MAX);
    ASSERT_EQ(testSize.height(), INT32_MIN);
    
    testSize = Size{INT32_MIN, INT32_MIN};
    ASSERT_EQ(testSize.width(), INT32_MIN);
    ASSERT_EQ(testSize.height(), INT32_MIN);
}


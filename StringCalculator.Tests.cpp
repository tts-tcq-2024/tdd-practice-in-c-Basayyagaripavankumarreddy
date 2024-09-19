#include <gtest/gtest.h>
#include "StringCalculator.h"

// Test for empty input
TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedResult = 0;
    const char* input = "";
    int result = Add(input);
    ASSERT_EQ(result, expectedResult);
}

// Test for single zero
TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedResult = 0;
    const char* input = "0";
    int result = Add(input);
    ASSERT_EQ(result, expectedResult);
}

// Test for sum of two numbers
TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedResult = 3;
    const char* input = "1,2";
    int result = Add(input);
    ASSERT_EQ(result, expectedResult);
}

// Test for sum with newline as delimiter
TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedResult = 6;
    const char* input = "1\n2,3";
    int result = Add(input);
    ASSERT_EQ(result, expectedResult);
}

// Test for ignoring numbers greater than 1000
TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedResult = 1;
    const char* input = "1,1001";
    int result = Add(input);
    ASSERT_EQ(result, expectedResult);
}

// Test for sum with custom delimiter
TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedResult = 3;
    const char* input = "//;\n1;2";
    int result = Add(input);
    ASSERT_EQ(result, expectedResult);
}

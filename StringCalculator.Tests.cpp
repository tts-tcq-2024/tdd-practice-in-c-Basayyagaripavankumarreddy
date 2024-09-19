#include <gtest/gtest.h>
#include "StringCalculator.h"  // Include your StringCalculator.h that defines Add() and related functions

// Test for empty input
TEST(StringCalculatorTests, ExpectZeroForEmptyInput) {
    int expected = 0;
    int result = Add("");
    ASSERT_EQ(result, expected);
}

// Test for single number
TEST(StringCalculatorTests, ExpectSingleNumber) {
    int expected = 5;
    int result = Add("5");
    ASSERT_EQ(result, expected);
}

// Test for two numbers
TEST(StringCalculatorTests, ExpectSumForTwoNumbers) {
    int expected = 3;
    int result = Add("1,2");
    ASSERT_EQ(result, expected);
}

// Test for handling newlines as delimiters
TEST(StringCalculatorTests, ExpectSumWithNewlineDelimiter) {
    int expected = 6;
    int result = Add("1\n2,3");
    ASSERT_EQ(result, expected);
}

// Test for ignoring numbers greater than 1000
TEST(StringCalculatorTests, IgnoreNumbersGreaterThan1000) {
    int expected = 2;
    int result = Add("2,1001");
    ASSERT_EQ(result, expected);
}

// Test for custom single character delimiter
TEST(StringCalculatorTests, ExpectSumWithCustomSingleCharacterDelimiter) {
    int expected = 6;
    int result = Add("//;\n1;2;3");
    ASSERT_EQ(result, expected);
}

// Test for custom multi-character delimiter
TEST(StringCalculatorTests, ExpectSumWithCustomMultiCharacterDelimiter) {
    int expected = 6;
    int result = Add("//[***]\n1***2***3");
    ASSERT_EQ(result, expected);
}

// Test for multiple custom delimiters
TEST(StringCalculatorTests, ExpectSumWithMultipleCustomDelimiters) {
    int expected = 10;
    int result = Add("//[;][%]\n1;2%3;4");
    ASSERT_EQ(result, expected);
}

// Test for negative numbers throwing exception
TEST(StringCalculatorTests, ExpectExceptionForNegativeNumbers) {
    char negativeNumbers[100] = {0};
    int numArray[MAX_NUMBERS] = {-1, 2, -3};
    int count = 3;

    int isNegative = ValidateNumbers(numArray, count, negativeNumbers);
    ASSERT_EQ(isNegative, 1);
    ASSERT_STREQ(negativeNumbers, "-1,-3");
}

// Test to ensure no exception for valid numbers
TEST(StringCalculatorTests, ValidatePositiveNumbers) {
    char negativeNumbers[100] = {0};
    int numArray[MAX_NUMBERS] = {1, 2, 3};
    int count = 3;

    int isNegative = ValidateNumbers(numArray, count, negativeNumbers);
    ASSERT_EQ(isNegative, 0);
}

// Test for sum of valid numbers
TEST(StringCalculatorTests, SumValidNumbers) {
    int numArray[MAX_NUMBERS] = {1, 2, 3, 1001};
    int count = 4;

    int sum = SumNumbers(numArray, count);
    ASSERT_EQ(sum, 6);  // Numbers greater than 1000 should be ignored
}

// Test for no input case
TEST(StringCalculatorTests, NoInputCase) {
    int expected = 0;
    int result = Add(NULL);
    ASSERT_EQ(result, expected);
}

// Test for extracting custom delimiter
TEST(StringCalculatorTests, ExtractCustomDelimiterTest) {
    char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH] = {",", "\n"};
    int delimiterCount = 2;
    char* numberString = ExtractCustomDelimiter("//[***]\n1***2***3", delimiters, &delimiterCount);
    
    ASSERT_STREQ(numberString, "1***2***3");
    ASSERT_STREQ(delimiters[delimiterCount - 1], "***");
    ASSERT_EQ(delimiterCount, 3);  // Default 2 + 1 custom delimiter
}

// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

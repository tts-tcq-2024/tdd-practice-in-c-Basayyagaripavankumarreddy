#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringCalculator.h"  // Assuming you have the StringCalculator implemented as in the previous solution.

// Test function declarations
void test_ExpectZeroForEmptyInput(void);
void test_ExpectZeroForSingleZero(void);
void test_ExpectSumForTwoNumbers(void);
void test_ExpectExceptionForNegativeNumbers(void);
void test_ExpectSumWithNewlineDelimiter(void);
void test_IgnoreNumbersGreaterThan1000(void);
void test_ExpectSumWithCustomDelimiter(void);

// Setup before each test (optional)
void setUp(void) {}

// Tear down after each test (optional)
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_ExpectZeroForEmptyInput);
    RUN_TEST(test_ExpectZeroForSingleZero);
    RUN_TEST(test_ExpectSumForTwoNumbers);
    RUN_TEST(test_ExpectExceptionForNegativeNumbers);
    RUN_TEST(test_ExpectSumWithNewlineDelimiter);
    RUN_TEST(test_IgnoreNumbersGreaterThan1000);
    RUN_TEST(test_ExpectSumWithCustomDelimiter);

    return UNITY_END();
}

// Test function implementations
void test_ExpectZeroForEmptyInput(void) {
    int expectedResult = 0;
    const char* input = "";
    int result = Add(input);
    TEST_ASSERT_EQUAL_INT(expectedResult, result);
}

void test_ExpectZeroForSingleZero(void) {
    int expectedResult = 0;
    const char* input = "0";
    int result = Add(input);
    TEST_ASSERT_EQUAL_INT(expectedResult, result);
}

void test_ExpectSumForTwoNumbers(void) {
    int expectedResult = 3;
    const char* input = "1,2";
    int result = Add(input);
    TEST_ASSERT_EQUAL_INT(expectedResult, result);
}

void test_ExpectExceptionForNegativeNumbers(void) {
    const char* input = "-1,2";
    if (setjmp(Unity.AbortFrame) == 0) { // Handle exception manually using setjmp (optional)
        Add(input);
        TEST_FAIL_MESSAGE("Expected exception for negative numbers but none thrown");
    } else {
        printf("negatives not allowed: -1\n");
    }
}

void test_ExpectSumWithNewlineDelimiter(void) {
    int expectedResult = 6;
    const char* input = "1\n2,3";
    int result = Add(input);
    TEST_ASSERT_EQUAL_INT(expectedResult, result);
}

void test_IgnoreNumbersGreaterThan1000(void) {
    int expectedResult = 1;
    const char* input = "1,1001";
    int result = Add(input);
    TEST_ASSERT_EQUAL_INT(expectedResult, result);
}

void test_ExpectSumWithCustomDelimiter(void) {
    int expectedResult = 3;
    const char* input = "//;\n1;2";
    int result = Add(input);
    TEST_ASSERT_EQUAL_INT(expectedResult, result);
}


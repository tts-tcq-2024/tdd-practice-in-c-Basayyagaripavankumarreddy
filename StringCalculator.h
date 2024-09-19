#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBERS 100
#define MAX_DELIMITERS 10
#define MAX_DELIMITER_LENGTH 10

// Function declarations
int Add(const char* numbers);
char* ExtractCustomDelimiter(const char* numbers, char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH], int* delimiterCount);
void AddCustomDelimiters(const char* delimiterSection, char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH], int* delimiterCount);
int SplitNumbers(const char* numbers, char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH], int delimiterCount, int numArray[MAX_NUMBERS]);
void ValidateNumbers(int numArray[MAX_NUMBERS], int count);
int SumNumbers(int numArray[MAX_NUMBERS], int count);

// Main Add function
int Add(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }

    char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH] = { ",", "\n" }; // Default delimiters
    int delimiterCount = 2;

    char* numberString = ExtractCustomDelimiter(numbers, delimiters, &delimiterCount);

    int numArray[MAX_NUMBERS];
    int count = SplitNumbers(numberString, delimiters, delimiterCount, numArray);

    ValidateNumbers(numArray, count);

    return SumNumbers(numArray, count);
}

// Function to extract custom delimiters
char* ExtractCustomDelimiter(const char* numbers, char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH], int* delimiterCount) {
    if (numbers[0] == '/' && numbers[1] == '/') {
        const char* endOfDelimiter = strchr(numbers, '\n');
        char delimiterSection[100];

        strncpy(delimiterSection, numbers + 2, endOfDelimiter - numbers - 2);
        delimiterSection[endOfDelimiter - numbers - 2] = '\0';

        AddCustomDelimiters(delimiterSection, delimiters, delimiterCount);
        return (char*)(endOfDelimiter + 1);
    }
    return (char*)numbers;
}

// Function to add custom delimiters
void AddCustomDelimiters(const char* delimiterSection, char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH], int* delimiterCount) {
    if (delimiterSection[0] == '[' && delimiterSection[strlen(delimiterSection) - 1] == ']') {
        strncpy(delimiters[(*delimiterCount)], delimiterSection + 1, strlen(delimiterSection) - 2);
        delimiters[(*delimiterCount)][strlen(delimiterSection) - 2] = '\0';
        (*delimiterCount)++;
    } else {
        strcpy(delimiters[(*delimiterCount)], delimiterSection);
        (*delimiterCount)++;
    }
}

// Function to split the numbers based on delimiters
int SplitNumbers(const char* numbers, char delimiters[MAX_DELIMITERS][MAX_DELIMITER_LENGTH], int delimiterCount, int numArray[MAX_NUMBERS]) {
    char numString[1000];
    strcpy(numString, numbers);
    
    char* token;
    int count = 0;
    char* rest = numString;

    while ((token = strtok_r(rest, delimiters[0], &rest))) {
        for (int i = 1; i < delimiterCount; i++) {
            if (strpbrk(token, delimiters[i])) {
                token = strtok(token, delimiters[i]);
            }
        }
        numArray[count++] = atoi(token);
    }
    return count;
}

// Function to validate numbers (checking for negatives)
void ValidateNumbers(int numArray[MAX_NUMBERS], int count) {
    int hasNegatives = 0;
    char negativeNumbers[100] = { 0 };

    for (int i = 0; i < count; i++) {
        if (numArray[i] < 0) {
            char numStr[10];
            sprintf(numStr, "%d,", numArray[i]);
            strcat(negativeNumbers, numStr);
            hasNegatives = 1;
        }
    }

    if (hasNegatives) {
        negativeNumbers[strlen(negativeNumbers) - 1] = '\0'; // Remove trailing comma
        printf("negatives not allowed: %s\n", negativeNumbers);
        exit(EXIT_FAILURE); // Exit if negative numbers are found
    }
}

// Function to sum the numbers, ignoring those greater than 1000
int SumNumbers(int numArray[MAX_NUMBERS], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        if (numArray[i] <= 1000) {
            sum += numArray[i];
        }
    }
    return sum;
}

// Test the Add function
int main() {
    printf("Sum: %d\n", Add("1,2,3"));
    printf("Sum: %d\n", Add("//[;]\n1;2;3"));
    printf("Sum: %d\n", Add("//;\n1;2;1001;3"));
    return 0;
}


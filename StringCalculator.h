#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Checks if the character is a digit (0-9)
int isCharacterDigit(char character) {
    return (character >= '0' && character <= '9');
}

// Prints an exception if the input has a negative number, along with the negative values
void printNegativeNumberException(int negativeNumbers[], int count) {
    printf("Exception: Negative numbers not allowed ");
    for (int i = 0; i < count; i++) {
        printf("%d ", negativeNumbers[i]);
    }
    printf("\n");
}

// Checks for two consecutive digits
int needsCommaInsertion(char currentChar, char nextChar) {
    return isCharacterDigit(currentChar) && isCharacterDigit(nextChar);
}

// Inserts a comma between two consecutive digits
void insertCommasBetweenConsecutiveDigits(char *inputString) {
    char temp[512];
    int commaIndex = 0;
    for (int i = 0; inputString[i] != '\0'; i++) {
        temp[commaIndex++] = inputString[i];
        if (needsCommaInsertion(inputString[i], inputString[i + 1])) {
            temp[commaIndex++] = ',';  
        }
    }
    temp[commaIndex] = '\0';
    strcpy(inputString, temp);  
}

// Checks if the next character in the input string is not a digit or if the string is null-terminated
int isNextCharNonDigit(char nextChar) {
    return (nextChar == '\0' || !isCharacterDigit(nextChar));
}

// Checks for invalid characters in the input string based on the delimiter
int containsInvalidSequence(char currentChar, char nextChar, char delimiterChar) {
    return currentChar == delimiterChar && isNextCharNonDigit(nextChar);
}

// Uses a helper function to check if the characters in the input string are valid digits, ignoring delimiters
int isInvalidInput(int i, const char* inputString) {
    return (containsInvalidSequence(inputString[i], inputString[i + 1], ',') ||
            containsInvalidSequence(inputString[i], inputString[i + 1], '\n'));
}

// Acts as a check to ensure the input is not a single invalid entry
int validateNonEmptyInput(const char *inputString) {
    int isValid = 1;
    for (int i = 0; inputString[i] != '\0'; i++) {
        if (isInvalidInput(i, inputString)) {
            printf("Exception: Invalid input sequence at position %d.\n", i);
            isValid = 0;
        }
    }
    return isValid;
}

// Checks if the input string contains valid digits for further processing
int hasDigits(const char* inputString) {
    int containsDigit = 0;
    for (int i = 0; inputString[i] != '\0'; i++) {
        if (isCharacterDigit(inputString[i])) {
            containsDigit = 1;
        }
    }
    return !containsDigit;
}

// Checks for non-numeric or empty input strings
int isInvalidOrEmptyInput(const char *inputString) {
    return (strlen(inputString) == 0 || hasDigits(inputString));
}

// Checks if the input has a custom delimiter format
int hasCustomDelimiter(char *inputStringCopy) {
    return strncmp(inputStringCopy, "//", 2) == 0;
}

// Ensures the end index is greater than the start index of the input string for valid length
int isInputRangeValid(char *start, char *end) {
    return (end > start);
}

// Parses the input string characters only if the length is non-zero
int isInputNotNull(char *start, char *end) {
    return (start != NULL && end != NULL);
}

// Initial checks for a valid input string with custom delimiter
int isValidDelimiterRange(char *start, char *end) {
    return (isInputNotNull(start, end) && isInputRangeValid(start, end));
}

// Extracts the custom delimiter based on the specified format
void parseCustomDelimiter(char *inputStringCopy, char *delimiter) {
    char *start = strchr(inputStringCopy, '[');
    char *end = strchr(inputStringCopy, ']');
    if (isValidDelimiterRange(start, end)) {
        strncpy(delimiter, start + 1, end - start - 1);
        delimiter[end - start - 1] = '\0';
    }
}

// Handles cases where the custom delimiter is empty
void setDefaultDelimiterIfEmpty(char *inputString, char *delimiter) {
    if (strcmp(delimiter, "") == 0) {
        insertCommasBetweenConsecutiveDigits(inputString);
        strcpy(delimiter, ",");
    }
}

// Processes negative numbers, storing them in an array
int handleNegativeNumber(int number, int negativeNumbers[], int *negativeCount) {
    if (number < 0) {
        negativeNumbers[(*negativeCount)++] = number;
        return 0;
    }
    return 1;
}

// Adds to sum if the number is less than or equal to 1000
void addIfValid(int number, int *sum) {
    if (number <= 1000) {
        *sum += number;
    }
}

// Checks for a valid input string with custom delimiter
void validateDelimiter(char *inputStringCopy, char **numberString, char *delimiter) {
    if (hasCustomDelimiter(inputStringCopy)) {
        parseCustomDelimiter(inputStringCopy, delimiter);
        *numberString = strchr(inputStringCopy, '\n') + 1;
        setDefaultDelimiterIfEmpty(*numberString, delimiter);
    }
}

// Handles negative numbers in the input string and prints exceptions
int handleNegativeValues(int negativeCount, int negativeNumbers[], int sum) {
    if (negativeCount > 0) {
        printNegativeNumberException(negativeNumbers, negativeCount);
        sum = 0;
    }
    return sum;
}

// Calculates the final sum based on the input string and delimiter
int computeSum(char *numberString, char delimiter[]) {
    char *token = strtok(numberString, delimiter);
    int sum = 0;
    int negativeNumbers[256];
    int negativeCount = 0;
    while (token != NULL) {
        int number = atoi(token);
        if (!handleNegativeNumber(number, negativeNumbers, &negativeCount)) {
            token = strtok(NULL, delimiter);
            continue;
        }
        addIfValid(number, &sum);
        token = strtok(NULL, delimiter);
    }
    sum = handleNegativeValues(negativeCount, negativeNumbers, sum);
    return sum;
}

// Main function to process input and compute the result
int add(const char *inputString) {
    int result = 0;
    if (isInvalidOrEmptyInput(inputString)) {
        return 0;
    }
    char inputCopy[512];
    strcpy(inputCopy, inputString);
    char delimiter[256] = ",\n;";
    char *numberString = inputCopy;
    validateDelimiter(inputCopy, &numberString, delimiter);
    if (validateNonEmptyInput(numberString)) {
        result = computeSum(numberString, delimiter);
    }
    return result;
}

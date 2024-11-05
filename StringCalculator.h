#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int add(const char* input);

// Function to replace newline characters with commas
void replace_newline_with_comma(char* input) {
    for (char* p = input; *p; ++p) {
        if (*p == '\n') {
            *p = ',';  // Replace newline with comma
        }
    }
}

// Function to check if the input string has numbers
int Check_numbers(const char* input) {
    while (*input) {
        if (isdigit(*input)) {
            return 0;  // Return 0 (true) if any digit is found
        }
        input++;  // Move to the next character
    }
    return 1;  // Return 1 if no digits are found
}

// Function to check if the input string is empty
int isEmpty(const char* input) {
    return (input[0] == '\0');  // Return 1 if string is empty, 0 otherwise
}

// Function to check if the input string is a single zero
int SingleZero(const char* input) {
    return (strcmp(input, "0") == 0); // Return 1 if input is "0"
}

// Function to check if the input numbers are valid for addition
int number_if_valid(int number) {
    return (number <= 1000 && number >= 0);
}

// This function checks for two consecutive digits
int shouldInsertComma(char currentChar, char nextChar) {
    return isdigit(currentChar) && isdigit(nextChar);
}

// This function inserts a comma between two consecutive digits
void insertCommasBetweenDigits(char *numbers) {
    char temp[512];
    int commaIndex = 0;
    for (int index = 0; numbers[index] != '\0'; index++) {
        temp[commaIndex++] = numbers[index];
        if (shouldInsertComma(numbers[index], numbers[index + 1])) {
            temp[commaIndex++] = ',';  
        }
    }
    temp[commaIndex] = '\0';
    strcpy(numbers, temp);  
}

// This helper function ensures the end index is greater than the start index of the input string i.e., valid length
int parseInputIfValid(char *start, char *end) {
    return (end > start);
}

// This helper function parses the input string characters only if its length is non-zero
int parseInputIfNotNull(char *start, char *end) {
    return (start != NULL && end != NULL);
}

// This function does the initial valid input string checks for custom delimiter functionality
int parseInput(char *start, char *end) {
    return (parseInputIfNotNull(start, end) && parseInputIfValid(start, end));
}

// This function extracts the delimiter based on the given format
void extractCustomDelimiter(char *stringCopy, char *delimiter) {
    char *start = strchr(stringCopy, '[');
    char *end = strchr(stringCopy, ']');
    if (parseInput(start, end)) {
        strncpy(delimiter, start + 1, end - start - 1);
        delimiter[end - start - 1] = '\0';
    }
}

// This function handles a case where the custom delimiter is empty
void handleEmptyDelimiter(char *numbers, char *delimiter) {
    if (strcmp(delimiter, "") == 0) {
        insertCommasBetweenDigits(numbers);
        strcpy(delimiter, ",");
    }
}

// Placeholder function to check if a custom delimiter is specified (implement as needed)
int isCustomDelimiter(const char *input) {
    return strncmp(input, "//", 2) == 0;
}

// Placeholder function to get modified input (implement as needed)
char* getModifiedInput(const char *input, const char **delimiter) {
    char *modifiedInput = strdup(input);  // Copy input to modifiable buffer
    replace_newline_with_comma(modifiedInput);
    return modifiedInput;
}

// This function combines all the helper functions to check for a valid input string with custom delimiter
void validateCustomDelimiter(char *stringCopy, char **numbers, char *delimiter) {
    if (isCustomDelimiter(stringCopy)) {
        extractCustomDelimiter(stringCopy, delimiter);
        *numbers = strchr(stringCopy, '\n') + 1;
        handleEmptyDelimiter(*numbers, delimiter);
    }
}

// Function to add valid inputs
int AddifValid(const char* input, const char* delimiter) {
    int sum = 0;
    char* modifiedInput = getModifiedInput(input, &delimiter);
    char* token = strtok(modifiedInput, delimiter);  // Tokenize by the custom delimiter
    while (token) {
        int number = atoi(token);  // Convert token to integer
        if (number_if_valid(number)) {
            sum += number;  // Add to sum if the number is valid
        }
        token = strtok(NULL, delimiter);  // Continue tokenizing with the custom delimiter
    }
    free(modifiedInput);  // Free allocated memory
    return sum;
}

// Main function to add numbers based on input
int add(const char* input) {
    // Create a copy of the input
    char input_copy[100];
    char delimiter[10] = ",";  // Default delimiter is a comma
    char *numbers;

    strncpy(input_copy, input, sizeof(input_copy) - 1);
    input_copy[sizeof(input_copy) - 1] = '\0';  // Ensure null termination

    int returnEmpty = 0;

    returnEmpty |= isEmpty(input_copy);
    returnEmpty |= Check_numbers(input_copy);
    returnEmpty |= SingleZero(input_copy);

    validateCustomDelimiter(input_copy, &numbers, delimiter);

    if (returnEmpty == 1) {
        return 0;
    } else {
        return AddifValid(numbers, delimiter);
    }
}

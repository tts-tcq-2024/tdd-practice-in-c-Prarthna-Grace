#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>

int add(const char* input);

// Function to handle custom delimiter logic
char* getModifiedInput(const char* input, char* delimiter) {
    char* modifiedInput = strdup(input);
    *delimiter = ','; // Default delimiter

    if (strncmp(modifiedInput, "//", 2) == 0) {
        // Custom delimiter found
        *delimiter = modifiedInput[2];
        modifiedInput = modifiedInput + 4; // Skip the delimiter part (e.g., "//;\n")
    }
    replace_newline_with_comma(input_copy);  // Replace newlines with commas
    return modifiedInput;
}


//Function to check if the input string has numbers
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

// Function to replace newline characters with commas
void replace_newline_with_comma(char* input) {
    for (char* p = input; *p; ++p) {
        if (*p == '\n') {
            *p = ',';  // Replace newline with comma
        }
    }
}

//Function to check if the input numbers are valid for addition
int number_if_valid(int number) 
{
return (number <= 1000 && number>=0);
}

//Function to add valid inputs
int AddifValid(const char* input, const char* delimiter) {
    int sum = 0;
    char* modifiedInput = getModifiedInput(input, &delimiter);
    char* token = strtok( modifiedInput, &delimiter);  // Tokenize by the custom delimiter
    while (token) {
        int number = atoi(token);  // Convert token to integer
        if (number_if_valid(number)) {
            sum += number;  // Add to sum if the number is valid
        }
        token = strtok(NULL, &delimiter);  // Continue tokenizing with the custom delimiter
    }
    return sum;
}

int add(const char* input){
    // Create a copy of the input
    char input_copy[100];
    char delimiter[10] = ","; // Default delimiter is a comma
    strncpy(input_copy, input, sizeof(input_copy) - 1);
    input_copy[sizeof(input_copy) - 1] = '\0';  // Ensure null termination
    int len= strlen(input_copy); 
    int returnEmpty=0, result=0; 
    returnEmpty |= isEmpty(input_copy);
    returnEmpty |= Check_numbers(input_copy);
    returnEmpty |= SingleZero(input_copy);
    if(returnEmpty == 1)
    { 
        return 0;
    }
    else
    {
        return AddifValid(input_copy, delimiter);
    } 
}



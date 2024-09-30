#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>

int add(const char* input);

// Function to handle custom delimiter logic
void handle_custom_delimiter(char* input, char* delimiter) {
    if (strncmp(input, "//", 2) == 0) {
        char* newline_pos = strchr(input, '\n');
        if (newline_pos) {
            *newline_pos = '\0';  // Terminate the string at the newline
            strcpy(delimiter, input + 2);  // Copy the delimiter after "//"
            // Move input pointer to the part after the delimiter
            input = newline_pos + 1;  
        }
    }
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
    char* input_copy = strdup(input);  // Duplicate input string
    char* token = strtok(input_copy, delimiter);  // Tokenize by the custom delimiter

    while (token) {
        int number = atoi(token);  // Convert token to integer
        if (number_if_valid(number)) {
            sum += number;  // Add to sum if the number is valid
        }
        token = strtok(NULL, delimiter);  // Continue tokenizing with the custom delimiter
    }
    free(input_copy);  // Free the duplicated string
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
        handle_custom_delimiter(input_copy, delimiter); // Handle custom delimiter
        replace_newline_with_comma(input_copy);  // Replace newlines with commas
        return AddifValid(input_copy + strlen(delimiter) + 1, delimiter);
    } 
}



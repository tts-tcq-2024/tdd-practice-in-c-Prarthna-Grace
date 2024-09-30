#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>

int add(const char* input);

// Function to replace custom delimiter
void replace_custom_delimiter(char* input, const char* delimiter) {
    char* pos;
    size_t delimiter_length = strlen(delimiter);
    
    while ((pos = strstr(input, delimiter)) != NULL) {
        *pos = ',';  // Replace first character of the delimiter with a comma
        memmove(pos + 1, pos + delimiter_length, strlen(pos + delimiter_length) + 1); // Shift the rest of the string
    }
}

// Function to handle custom delimiter logic
void handle_custom_delimiter(char* input) {
    if (strncmp(input, "//", 2) == 0) {
        char* newline_pos = strchr(input, '\n');
        if (newline_pos) {
            *newline_pos = '\0';  // Terminate string at newline
            const char* delimiter = input + 2;  // Get the delimiter
            replace_custom_delimiter(newline_pos + 1, delimiter);  // Replace custom delimiter
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
int AddifValid(const char* input) {
    int sum = 0;
    char* input_copy = strdup(input);  // Duplicate input string
    char* token = strtok(input_copy, ",");  // Tokenize by comma

    while (token) {
        int number = atoi(token);  // Convert token to integer
        if (number_if_valid(number)) {
            sum += number;  // Add to sum if the number is 1000 or less
        }
        token = strtok(NULL, ",");  // Continue tokenizing
    }
    free(input_copy);  // Free the duplicated string
    return sum;
}

int add(const char* input){
    // Create a copy of the input
    char input_copy[100];
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
        // Handle custom delimiter
        handle_custom_delimiter(input_copy);
        replace_newline_with_comma(input_copy);  // Replace newlines with commas
        result = AddifValid(input_copy);
        return result;
    } 
}



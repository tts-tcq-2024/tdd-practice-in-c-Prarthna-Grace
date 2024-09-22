#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>

int add(const char* input);

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
int SingleZero(const char*input){
    return (input[0]=='0');    
}

// Function to replace newline characters with commas
void replace_newline_with_comma(char* input) {
    for (char* p = input; *p; ++p) {
        if (*p == '\n') {
            *p = ',';  // Replace newline with comma
        }
    }
}

int AddifValid(const char* input) {
    int sum = 0;
    char* input_copy = strdup(input);  // Duplicate input to avoid modifying the original
    char* token = strtok(input_copy, ",");  // Tokenize by comma
    
    while (token) {
        sum += atoi(token);  // Convert token to integer and add to sum
        token = strtok(NULL, ",");  // Continue tokenizing
    }

    free(input_copy);  // Free the duplicated string
    return sum;
}

int add(const char* input){
    int len= strlen(input); 
    int returnEmpty=0, result=0; 
    returnEmpty |= isEmpty(input);
    returnEmpty |= Check_numbers(input);
    if(len==1){
        returnEmpty |= SingleZero(input);
    }
    if(returnEmpty == 1)
    { 
        return 0;
    }
    else
    {
        replace_newline_with_comma(input_copy);  // Replace newlines with commas
        result = AddifValid(input);
        return result;
    } 
}

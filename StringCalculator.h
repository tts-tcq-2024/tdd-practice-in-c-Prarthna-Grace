#include<stdio.h>
#include<string.h>
#include <ctype.h>

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

int AddifValid(const char* input) {
    // Assumes input is in the format "a,b"
    if (input[1] == ',') {
        // Convert the characters to integers and add them
        return (input[0] - '0') + (input[2] - '0');
    }
    return 0;  // Return 0 if format is invalid
}

int replace_newline_with_comma(const char* input){
    for (char* p = input; *p; ++p){
        if (*p == '\n') {
            input[0] = input[0] - '0' + input[1] - '0' ;  // Replace newline with comma 
            return input;
        }
    }
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
        int input_copy= replace_newline_with_comma(input);
        result = AddifValid(input_copy);
        return result;
    } 
}

#include<stdio.h>
#include<string.h>
#include <ctype.h>

int add(const char* input);

//Function to check if the input string has numbers
int Check_numbers(const char* input) {
    while (*input) {
        if (isdigit(*input)) {
            return 1;  // Return 1 (true) if any digit is found
        }
        input++;  // Move to the next character
    }
    return 0;  // Return 0 if no digits are found
}

// Function to check if the input string is empty
int isEmpty(const char* input) {
    return (input[0] == '\0');  // Return 1 if string is empty, 0 otherwise
}

// Function to check if the input string is a single zero
int SingleZero(const char*input, int len)
{
    if(len ==1 && input[0]==0)
        return 0;
}

int add(const char* input){
    if (isEmpty(input) || !(Check_numbers(input))) {
        return 0;  // Return 0 if the input is empty or contains no digits
    }
    int len= strlen(input);
    SingleZero(input,len);  
}




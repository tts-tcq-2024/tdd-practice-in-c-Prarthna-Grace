#include "StringCalculator.h"
#include<string.h>
#include <ctype.h>

//Function to check if the input string has numbers
int Check_numbers(const char* input){
  while(*input){
    return (isdigit(*input));
  }
}
// Function to check if the input string is empty
int isEmpty(const char* input) {
    return (input[0] == '\0');  // Return 1 if string is empty, 0 otherwise
}

int add(const char*input){
  char result[];
  if((!(Check_numbers(input))) || isEmpty(input)){
      result[0]='\0';
   }
  return result;
}
  


#include "StringCalculator.h"
#include<string.h>
#include <ctype.h>

int isEmpty(const char* input){
  return (isdigit(*input));
}

void String_function(const char*input, char* result){
  if(!(isEmpty(input))){
      result[0]='\0';
   }
  


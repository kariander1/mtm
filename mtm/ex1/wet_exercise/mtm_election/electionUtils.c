
#ifndef ELECTION_UTILS_C_
#define ELECTION_UTILS_C_

#include <stdlib.h>
#include <string.h>
#include "electionUtils.h"


int stringToInt(char* str);
char *intToString(int int_to_convert);
static int getNumOfDigits(int number);


int stringToInt(char* str)
{
    return atoi(str);
}
char *intToString(int int_to_convert)
{
    int num_of_digits = getNumOfDigits(int_to_convert); // check the log to se  how many chars we need for the itoa() function

    char *string_of_int = malloc(sizeof(char) * num_of_digits + 1); // +1 for "/0"  
    RETURN_ON_NULL(string_of_int, NULL);                 // check if allocation failed - if so returns NULL in string_of_int
    RETURN_ON_NULL(itoa(int_to_convert, string_of_int, NUMBERING_BASE), NULL);
  
    //const char *const_string_to_int = string_of_int;

    return string_of_int;
}
static int getNumOfDigits(int number)
{
    int digits=0;
    do
    {
        digits++;
        number/=10;
    } while(number);
    return digits;
}

#endif

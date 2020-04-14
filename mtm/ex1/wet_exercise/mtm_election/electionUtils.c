
#ifndef ELECTION_UTILS_C_
#define ELECTION_UTILS_C_

#include <stdlib.h>
#include <math.h>
#include "electionUtils.h"

#define NUMBERING_BASE 10



int stringToInt(char* str)
{
    
    return atoi(str);
}
char *intToString(int int_to_convert)
{
    int num_of_digits = ceil(log10(int_to_convert)); // check the log to se  how many chars we need for the itoa() function

    char *string_of_int = malloc(sizeof(char) * num_of_digits + 1); // +1 for "/0" ceil rounds the double up
    RETURN_ON_CONDITION(string_of_int, NULL, NULL);                 // check if allocation failed - if so returns NULL in string_of_int
    RETURN_ON_CONDITION(itoa(int_to_convert, string_of_int, NUMBERING_BASE),NULL, NULL);
  
    //const char *const_string_to_int = string_of_int;

    return string_of_int;
}



#endif

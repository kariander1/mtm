
#ifndef UTILS_C_
#define UTILS_C_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "exutilities.h"
#define NUMBERING_BASE 10


/**
* getNumOfDigits: Gets the number of digits of a non-negative number
*
* @param number - The number to get digits from
* @return
* 	int of number of digits
*/
static int getNumOfDigits(int number);


int stringToInt(const char* str)
{
    return atoi(str);
}
char *intToString(const int int_to_convert)
{
    int num_of_digits = getNumOfDigits(int_to_convert); // check the log to se  how many chars we need for the itoa() function

    char *string_of_int = malloc(sizeof(char) * num_of_digits + 1); // +1 for "/0"  
    RETURN_ON_NULL(string_of_int, NULL);                 // check if allocation failed - if so returns NULL in string_of_int
 
    if(sprintf(string_of_int,"%d",int_to_convert)<0)
    {
        free(string_of_int);
        return NULL;
    }

    return string_of_int;
}
char *getCopyOfString(const char* str)
{
    RETURN_ON_NULL(str,NULL);
    char * copy_of_str = malloc(sizeof(char)*strlen(str)+1);
    RETURN_ON_NULL(copy_of_str,NULL);
    strcpy(copy_of_str,str);
    return copy_of_str;
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

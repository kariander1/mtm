#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*  function duplicates a given string the given amount of times
 Error Codes:  Allocation error in malloc - returns NULL
 Returns    :  Pointer to string duplicated the amount of times requested*/
char *duplicateString(char *str, int times)
{
    assert(str);
    assert(times > 0);
    int len = strlen(str);
    char *str_out = malloc((len * times)+1); // +1 for the \0
    assert(str_out);
    if(!str_out)
    {
        return NULL;
    }
    for (int i = 0; i < times; i++)
    {// Last character \0 is being overriden except for the last iteration
        strcpy(str_out+i*len, str);
    }
    return str_out;
}
int main()
{
    char *str = "yo";
    char *newstr =duplicateString(str,0);

    printf("%s",newstr);
    return 0;
}
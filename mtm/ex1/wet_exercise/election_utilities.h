
#ifndef UTILS_h_
#define UTILS_h_


/**
* intToString: Converts an int to an array of characters
*
* @param int_to_convert - The integer that is desired to convert
* @return
* 	String representation of the number. **NOTE** - the string is malloced and should be freed.
*   In case of memory allocation failure - NULL.
*/
char *intToString(const int int_to_convert);
/**
* stringToInt: Converts a int to an array of characters
*
* @param str - The string representation of the number
* @return
* 	Int representation of the string
*/
int stringToInt(const char* str);
/**
* getCopyOfString: Return a copy of the string given
*
* @param str - The string desired to copy
* @return
* 	Copy of the string with malloc
*/
char *getCopyOfString(const char* str);
/**
* xmalloc: Simulates malloc failures, otherwise mallocs the same amount given.
*          xmalloc will fail every "fail_after" times variable at electionUtils.c
*
* @param size - The size o bytes to allocate
* @return
* 	Pointer to the first block allocated or NULL on a *SIMULATED* failure
*/
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z') 

#endif

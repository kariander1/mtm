
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
/*!
* Macro for returning whether a char is lower case
*/
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z') 


#endif

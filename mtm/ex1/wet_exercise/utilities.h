
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
void *xmalloc(size_t size);
/**
* xrealloc: Simulates realloc failures, otherwise mallocs the same amount given.
*          xmalloc will fail every "fail_after" times variable at electionUtils.c
*
* @param size - The size o bytes to allocate
* @return
* 	Pointer to the first block allocated or NULL on a *SIMULATED* failure
*/
void *xrealloc(void *start_ptr,size_t size);
/*!
* Macro for shortening returning values for NULL or false objects
*/
#define RETURN_ON_NULL(object, return_value) \
if (!(object))\
{\
    return (return_value);\
}

/*!
* Macro for returning whether a char is lower case
*/
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z') 

/*!
* Macro for shortening returning values for a certain condition of a object.
*/
#define RETURN_ON_CONDITION(object,comparator, return_value) \
    if ((object) == (comparator))                                   \
    {                                                \
        return (return_value);                       \
    }

       
/*!
* Macro for shortening a return with a certain condition on the object.
*/
#define RETURN_ON_CONDITION_NO_VALUE(object,comparator) \
    if ((object) == (comparator))                                   \
    {                                                \
        return;                       \
    }
/*!
* Executes an expression given when a certain condition not taken, and return an according value
*/
#define EXECUTE_ON_NOT_CONDITION(object,comparator, expression,return_value) \
if ((object) != (comparator))\
{\
    expression;\
    return (return_value);\
}

/*!
* Executes an expression given when a certain condition is taken, and return an according value
*/
#define EXECUTE_ON_CONDITION(object,comparator, expression,return_value) \
if ((object) == (comparator))\
{\
    expression;\
    return (return_value);\
}

#endif

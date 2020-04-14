
#ifndef ELECTION_UTILS_h_
#define ELECTION_UTILS_h_


char *intToString(int int_to_convert);
int stringToInt(char* str);


/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_NONEXISTENCE(object, return_value) \
if (!(object))\
{\
    return (return_value);\
}
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z') 
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_CONDITION(object,comparator, return_value) \
    if ((object) == (comparator))                                   \
    {                                                \
        return (return_value);                       \
    }

    /*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define DESTROY_ON_CONDITION(object,comparator,election, return_value) \
    if ((object) == (comparator))                                   \
    {                                                \
        electionDestroy(election); \
        return return_value;                       \
    }
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_CONDITION_NO_VALUE(object,comparator) \
    if ((object) == (comparator))                                   \
    {                                                \
        return;                       \
    }
/*!
* Macro for shortening returning values for non-existence of a object with an extra expression to execute.
*/
#define EXECUTE_ON_CONDITION(object,comparator, expression,return_value) \
if ((object) == (comparator))\
{\
    expression;\
    return (return_value);\
}

#endif

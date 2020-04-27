#ifndef MACRO_h_
#define MACRO_h_
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

/*!
* Macro for shortening returning values for NULL or false objects
*/
#define RETURN_ON_NULL(object, return_value) \
if (!(object))\
{\
    return (return_value);\
}



#endif

#include "../election.h"

struct election_t
{
   Map tribes; // ID + name
   Area areas[];
};
typedef struct Area_t
{
    int area_id;
    char* area_name;
    Map votes;
    
} * Area;
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_NONEXISTENCE(object, return_value) \
if (!(object))\
{\
    return (return_value);\
}
/*!
* Macro for shortening returning values for non-existence of a object with an extra expression to execute.
*/
#define EXECUTE_ON_NONEXISTENCE(object, expression,return_value) \
if (!(object))\
{\
    expression;\
    return (return_value);\
}


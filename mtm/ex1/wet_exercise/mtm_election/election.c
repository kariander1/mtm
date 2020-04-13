#include "../election.h"

#define AREA_INITIAL_SIZE 5
struct election_t
{
   Map tribes; // ID + name
   Area* areas;
   int area_size;
   int allocated_size;
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
void initializeElectionAttributes(Election election){
    mapClear(election->tribes);
    election->tribes = NULL;
    areaClear(election->areas);
}

Election electionCreate(){
    Election new_Election = malloc(sizeof(*new_Election));
    assert(new_Election);
    RETURN_ON_NONEXISTENCE(new_Election, NULL);
    new_Election->tribes = malloc(sizeof(*(new_Election->tribes))*AREA_INITIAL_SIZE);
    initializeElectionAttributes(new_Election);

    return new_Election;
}

int main(){
    electionCreate();
}
#include "../election.h"
#include "../mtm_map/map.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define AREA_INITIAL_SIZE 5
struct election_t
{
   Map tribes; // ID + name
   Area area;
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

/* FUNCTUIONS REGARDING AREA:
- areaClear(Area area)
-


*/
void initializeElectionAttributes(Election election){
    mapClear(election->tribes);
    for(int x = 0; x <election->area_size; x++){
        //election->tribes[x] = NULL;
    }
    election->area_size = 0;
    election->allocated_size = AREA_INITIAL_SIZE;
    //areaClear(election->areas);
}

Election electionCreate(){
    Election new_Election = malloc(sizeof(*new_Election));
    assert(new_Election);
    RETURN_ON_NONEXISTENCE(new_Election, NULL); // check if new_election in NULL and return NULL if so
    new_Election->tribes = malloc(sizeof(new_Election->tribes)*AREA_INITIAL_SIZE); // create an initialized size of areas
    initializeElectionAttributes(new_Election); // initial all attributes to be null or 0 accordingly

    return new_Election;
}

int main(){
    electionCreate();
}
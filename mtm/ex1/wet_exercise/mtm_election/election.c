
#ifndef ELECTION_C
#define ELECTION_C

#include "../election.h"
#include "../mtm_map/map.h"
#include "../mtm_map/map.c"
#include "area.h"
#include "area.c"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define AREA_INITIAL_SIZE 1
#define AREA_MULTIPLIER_SIZE 2
#define AREA_NOT_FOUND -1
#define LEGAL_DELIMITER ' '
#define NUMBERING_BASE 10

struct election_t
{
    Map tribes;  // ID = key , name = value
    Area *areas; // Array of areas
    int area_count;
    int allocated_size;
};

static void areasDestroy(Election election);
static void initializeElectionAttributes(Election election);
static bool isLegalId(int id);
static bool isLegalName(const char* name);
static bool isLegalVotes(int votes);
static int getAreaIndexById(Election election,int id);
static bool multiplyAreasSize(Election election);
static char* intToChar(int int_to_convert);
static char* checkTribeExsistsAndReturnName(Election election, int tribe_id);

#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z') 
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_CONDITION(object,comparator, return_value) \
    if ((object) == comparator)                                   \
    {                                                \
        return (return_value);                       \
    }
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_NOT_CONDITION(object,comparator, return_value) \
    if ((object) != comparator)                                   \
    {                                                \
        return (return_value);                       \
    }
    /*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define DESTROY_ON_CONDITION(object,comparator,election, return_value) \
    if ((object) == comparator)                                   \
    {                                                \
        electionDestroy(election); \
        return return_value;                       \
    }
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_CONDITION_NO_VALUE(object,comparator) \
    if ((object) == comparator)                                   \
    {                                                \
        return;                       \
    }
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define EXECUTE_ON_CONDITION(object,comparator, expression,return_value) \
if ((object) == (comparator))\
{\
    expression;\
    return (return_value);\
}
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define EXECUTE_ON_NOT_CONDITION(object,comparator, expression,return_value) \
if ((object) != (comparator))\
{\
    expression;\
    return (return_value);\
}
/* FUNCTUIONS REGARDING AREA:
- areaClear(Area area)
- areaCreate()
- areaDestroy(Area area)
- areaChangeNumOfVotes(Area area, tribe_id, +-num_of_votes);
*/

Election electionCreate() //Shelly
{
    Election new_Election = malloc(sizeof(*new_Election));
    assert(new_Election);
    RETURN_ON_CONDITION(new_Election,NULL, NULL); // check if new_election in NULL and return NULL if so
    new_Election->tribes = mapCreate();// create Map tribes 
    RETURN_ON_CONDITION(new_Election->tribes,NULL, NULL); 
    new_Election->areas = malloc(sizeof(*new_Election->areas)*AREA_INITIAL_SIZE); // create an array of areas
    RETURN_ON_CONDITION(new_Election->areas,NULL, NULL);
    initializeElectionAttributes(new_Election); // initial all attributes to be null or 0 accordingly
    return new_Election;
}

void electionDestroy(Election election)
{
    RETURN_ON_CONDITION_NO_VALUE(election,NULL);
    mapDestroy(election->tribes);
    areasDestroy(election);
    free(election);
 
}

ElectionResult electionAddTribe(Election election, int tribe_id, const char *tribe_name) // Shelly
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(tribe_name, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    char* string_of_tribe_id = intToChar(tribe_id); // create the char* for the mapGet function
    if (string_of_tribe_id == NULL){
        free(string_of_tribe_id);
        electionDestroy(election);
        return  ELECTION_OUT_OF_MEMORY;
    }
    const char * const_string_of_tribe_id = string_of_tribe_id;
    EXECUTE_ON_NOT_CONDITION(mapGet(election->tribes, const_string_of_tribe_id), NULL, free(string_of_tribe_id),ELECTION_TRIBE_ALREADY_EXIST );
    EXECUTE_ON_CONDITION(isLegalName(tribe_name), false ,free(string_of_tribe_id), ELECTION_INVALID_NAME );
    mapPut(election->tribes,const_string_of_tribe_id,tribe_name); //add the new tribe
    free(string_of_tribe_id); // free the string after usage
    return ELECTION_SUCCESS; // Placeholder
}

ElectionResult electionAddArea(Election election, int area_id, const char *area_name)
{
     RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
     RETURN_ON_CONDITION(area_name, NULL,ELECTION_NULL_ARGUMENT);
     RETURN_ON_CONDITION(isLegalId(area_id), false, ELECTION_INVALID_ID);

    if(getAreaIndexById(election,area_id)!=AREA_NOT_FOUND)
    {
        return ELECTION_AREA_ALREADY_EXIST;
    }
    // Area doesn't exist
     RETURN_ON_CONDITION(isLegalName(area_name), false, ELECTION_INVALID_NAME);
     if (election->area_count == election->allocated_size)
     {
         DESTROY_ON_CONDITION(multiplyAreasSize(election),false,election,ELECTION_OUT_OF_MEMORY); // Wasn't able to allocate more space
     }
    
    Area new_area = areaCreate(area_id,area_name);
    RETURN_ON_CONDITION(new_area,NULL,ELECTION_OUT_OF_MEMORY);

    election->areas[election->area_count] = new_area;
     election->area_count++;
     return ELECTION_SUCCESS;
}

const char *electionGetTribeName(Election election, int tribe_id) // Shelly
{
    RETURN_ON_CONDITION(election, NULL, NULL);
    //does not check the tribe_id is leagal!
    char* tribe_name = checkTribeExsistsAndReturnName(election, tribe_id);
    RETURN_ON_CONDITION(tribe_name, NULL, NULL);
    const char* const_tribe_name = tribe_name;
    return const_tribe_name;
}
ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(area_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalVotes(num_of_votes), false, ELECTION_INVALID_VOTES);

    int area_index;
    RETURN_ON_CONDITION(area_index=getAreaIndexById(election,area_id),AREA_NOT_FOUND,ELECTION_AREA_NOT_EXIST);

    char* tribe_id_str; // you can use electionGetTribeName - returns NULL if tribe name not found
    DESTROY_ON_CONDITION(tribe_id_str =intToChar(area_id),NULL,election,ELECTION_OUT_OF_MEMORY);
    RETURN_ON_CONDITION(mapContains(election->tribes,tribe_id_str),false,ELECTION_TRIBE_NOT_EXIST);
    
  
    
    return ELECTION_SUCCESS;
}
ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes) // Shelly
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(area_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalVotes(num_of_votes), false, ELECTION_INVALID_VOTES);

    int area_index = getAreaIndexById(election, area_id);
    RETURN_ON_CONDITION(area_index, AREA_NOT_FOUND, ELECTION_AREA_NOT_EXIST);

    RETURN_ON_CONDITION(electionGetTribeName(election, tribe_id), NULL, ELECTION_TRIBE_NOT_EXIST);
    // areaChangeNumOfVotes(election->areas[area_index], tribe_id, 0-num_of_votes); -- NEED TO IMPLEMENT
    //DESTROY_ON_CONDITION(areaChangeNumOfVotes,NULL,election,ELECTION_OUT_OF_MEMORY)
    return ELECTION_SUCCESS; // Placeholder
}
ElectionResult electionSetTribeName(Election election, int tribe_id, const char *tribe_name) // Shai
{
    return ELECTION_SUCCESS;
}
ElectionResult electionRemoveTribe(Election election, int tribe_id)
{
    return ELECTION_SUCCESS;
}
ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area) //Shelly
{
    return ELECTION_SUCCESS; // Placeholder
}
Map electionComputeAreasToTribesMapping(Election election) // UNITED!
{
    return NULL; // Placeholder
}


// Static Helper functions

static int getAreaIndexById(Election election,int id)
{
    for (int i = 0; i < election->area_count; i++)
    {
         if(areaEquals(election->areas[i],id))
         {
             return i;
         }
    }
    return AREA_NOT_FOUND;
}
static bool multiplyAreasSize(Election election)
{
    election->areas = realloc(election->areas,(sizeof( election->areas))*(election->allocated_size*AREA_MULTIPLIER_SIZE));
    RETURN_ON_CONDITION(election->areas,NULL,false);
    election->allocated_size*=2;
    return true;
}
static bool isLegalVotes(int votes)
{
    return (votes>0);
}
static bool isLegalId(int id)
{
    return (id>=0);
}
static bool isLegalName(const char* name)
{

    char* iterating_char =malloc(strlen(name) +1) ;
    while (iterating_char)
    {
        if((!IS_LOWER(*iterating_char) )&& (!((*iterating_char)==(LEGAL_DELIMITER ))))
        {
            free(iterating_char);
            return false;
        }
        iterating_char++;
    }
    free(iterating_char);
    return true;
}
static char *intToChar(int int_to_convert)
{
    int num_of_digits = log10(int_to_convert); // check the log to se  how many chars we need for the itoa() function
    char *string_of_int = malloc(sizeof(char) * num_of_digits + 2); // +1 for "/0" +1 for round up
    RETURN_ON_CONDITION(string_of_int, NULL, NULL);                 // check if allocation failed - if so returns NULL in string_of_int
    RETURN_ON_CONDITION(itoa(int_to_convert, string_of_int, NUMBERING_BASE),NULL, NULL);
  
    //const char *const_string_to_int = string_of_int;

    return string_of_int;
}
static void initializeElectionAttributes(Election election)
{
    //mapClear(election->tribes);
    election->area_count = 0;
    election->allocated_size = AREA_INITIAL_SIZE;
    for (int x = 0; x < election->allocated_size; x++)
    {
        election->areas[x] = NULL; // dont need to clear the map because it wasn't created yet
    }
    return;
}

static void areasDestroy(Election election) // This is NOT areaDestroy!
{
    RETURN_ON_CONDITION_NO_VALUE(election,NULL);
    for (int i = 0; i < election->area_count; i++)
    {
        areaDestroy(election->areas[i]);
    }
    free(election->areas);
}
static char * checkTribeExsistsAndReturnName(Election election, int tribe_id){
    char* string_of_tribe_id = intToChar(tribe_id); // create the char* for the mapGet function
    RETURN_ON_CONDITION(string_of_tribe_id, NULL,ELECTION_OUT_OF_MEMORY );// check if allocation of string_of_int failed
    const char * const_string_of_tribe_id = string_of_tribe_id; // convert char to const char 
    char* tribe_name = mapGet(election->tribes, const_string_of_tribe_id); // check if tribe_id exsists
    free(string_of_tribe_id);
    return tribe_name; // return Tribe nam or NULL if the tribe doesnt exsists
}
//for gebug
int main()
{
    Election election1 = electionCreate();
    //electionAddTribe(election1, 55, "Test");
    //electionGetTribeName(election1, 55);
    checkTribeExsistsAndReturnName(election1, 55);
}

#endif //ELECTION_C
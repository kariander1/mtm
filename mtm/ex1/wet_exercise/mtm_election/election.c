
#ifndef ELECTION_C
#define ELECTION_C

#include "../election.h"
#include "../mtm_map/map.h"
#include "area.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define AREA_INITIAL_SIZE 1
#define AREA_MULTIPLIER_SIZE 2
#define AREA_NOT_FOUND -1
#define LEGAL_DELIMITER ' '

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
static bool isLegalName(char* name);
static const char* intToChar(int int_to_convert);
//for debug
static bool isLegalId(int id){
    return true;
}
static bool isLegalName(char* name){
    return true;
}
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
#define RETURN_ON_CONDITION_NO_VALUE(object,comparator) \
    if ((object) == comparator)                                   \
    {                                                \
        return;                       \
    }


/* FUNCTUIONS REGARDING AREA:
- areaClear(Area area)
- areaCreate()
- areaDestroy(Area area)
*/

Election electionCreate() //Shelly
{
    Election new_Election = malloc(sizeof(*new_Election));
    assert(new_Election);
    RETURN_ON_CONDITION(new_Election,NULL, NULL); // check if new_election in NULL and return NULL if so
    //Map tribes = mapCreate();
    //RETURN_ON_CONDITION(tribes,NULL, NULL); // I think we need to use MapCreate no? - I don't think so because the new_Election creates it
    new_Election->areas = malloc(sizeof(*new_Election->areas)*AREA_INITIAL_SIZE); // create an array of areas
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
static const char* intToChar(int int_to_convert) {
	double num_of_digits = log10(int_to_convert); // check the log to see how many chars we need for the itoa() function
	int total_digits_num = ceil(num_of_digits) + 1; // +1 for "/0" ceil rounds the double up
	char* string_of_int = malloc(sizeof(char)*total_digits_num);
	RETURN_ON_CONDITION(string_of_int, NULL, NULL);// check if allocation failed - if so returns NULL in string_of_int
	RETURN_ON_CONDITION(itoa(int_to_convert, string_of_int, 10), NULL, NULL); // check itoa return function
	const char* const_string_to_int = string_of_int; // convert to const char
	return const_string_to_int;
}
ElectionResult electionAddTribe(Election election, int tribe_id, const char *tribe_name) // Shelly
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(tribe_id, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(tribe_name, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    const char* string_of_tribe_id = intToChar(tribe_id); // create the car for the mapGet function
    RETURN_ON_CONDITION(string_of_tribe_id, NULL,ELECTION_OUT_OF_MEMORY );// check if allocation of string_of_int failed
    RETURN_ON_CONDITION(mapGet(election->tribes, string_of_tribe_id), false, ELECTION_INVALID_ID);
    //free(string_of_tribe_id); // free the string after usage
    RETURN_ON_CONDITION(isLegalName(tribe_name), false, ELECTION_INVALID_NAME);
    mapPut(election->tribes,string_of_tribe_id,tribe_name); // the free of string_of_tribe_id is done by mapClear
    free(string_of_tribe_id); // free the string after usage
    // You can use islegalID and isLegalNAME static functions located down V
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
         RETURN_ON_CONDITION(multiplyAreasSize(election),false,ELECTION_OUT_OF_MEMORY); // + End Program? Should ask...
     }
    
    Area new_area = areaCreate(area_id,area_name);
    RETURN_ON_CONDITION(new_area,NULL,ELECTION_OUT_OF_MEMORY);

    election->areas[election->area_count] = new_area;
     election->area_count++;
     return ELECTION_SUCCESS;
}
const char *electionGetTribeName(Election election, int tribe_id) // Shelly
{
    return ""; // Placeholder
}
ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    return ELECTION_SUCCESS;
}
ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes) // Shelly
{
    // You can use getAreaIndexById function
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
static void handleOutOfMemory()
{
    //?
}
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
static bool isLegalId(int id)
{
    return (id>=0);
}
static bool isLegalName(char* name)
{
    char iterating_char = name;
    while (iterating_char)
    {
        if(!IS_LOWER(iterating_char) && !iterating_char==LEGAL_DELIMITER )
        {
            return false;
        }
        iterating_char++;
    }
    return true;
    
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
//for gebug
int main()
{
    Election new_election = electionCreate();
    electionAddTribe(new_election, 55, "Test");
}

#endif //ELECTION_C
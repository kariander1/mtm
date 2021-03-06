

#include "election.h"
#include "mtm_map/map.h"
#include "area.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "exutilities.h"

#define AREA_INITIAL_SIZE 1
#define AREA_MULTIPLIER_SIZE 2
#define AREA_NOT_FOUND -1
#define LEGAL_DELIMITER ' '
#define EMPTY 0
#define NULL_POINTER -1

/**                     --NOTE--         
     * 
     * First implemetntation approach was to use ONLY maps for representing tribes areas and votes.
     * The idea was to store in the key of the map a concatination of a tribe & area ID deliminated
     * By the UNDERSCORE '_' charcter, thus creating a unified identifier for a vote, and storing
     * the number of votes in the value attribute of map.
     * 
     * Concluding this, the election struct would be:
     * struct election_t
     *   {
     * 
     *       Map tribes;  // key = tribe ID , name = tribe name
     *       Map areas; // key = tribe ID , name = tribe name
     *       Map votes; // key ="<area_ID><DELIMITER='_'><tribe_ID>"" , name = number of votes
     *   };
     * Following this approch we wanted to implement an ADT that will manipulate strings and handle
     * all allocations invloved.
     * 
     * HOWEVER - Due to different interpretations of ADT requirements and definitions, our
     * understanding from different forum answers it would be wrong to not implement another
     * ADT for representing tribes or areas, and so the following implementation was conducted.
     * 
     *                    --END OF NOTE  
   */
struct election_t
{

    Map tribes;         // key = tribe ID , name = tribe anem
    Area *areas;        // Array of areas, avoid duplication of another map-like implementation of Area.
    int area_count;     // Used internally for iterating on array of areas
    int allocated_size; // Allocated size for areas array
};

/**
* areasDestroy: Destroys all areas stored in election, used as part of election destroy
*
* @param election - The election in which the areas desired to destroy
* @return
* 	NONE
*/
static void areasDestroy(Election election);
/**
* isLegalId: Validates the ID given according to instructions (>=0)
*
* @param id - The ID to check
* @return
* 	True -  ID complies with the condition given
*   False - ID does not comply with the node
*/
static bool isLegalId(int id);
/**
* isLegalName: Validates the name given according to instructions (lowercase and ' ' as delimiters)
*
* @param name - The name to check
* @return
* 	True -  Name complies with the condition given
*   False - Name does not comply with the node
*/
static bool isLegalName(const char *name);
/**
* isLegalVotes: Validates the votes given according to instructions (non-negative)
*
* @param votes - The number of votes
* @return
* 	True -  Number of votes comply with the condition given
*   False - Number of votes does not comply with the node
*/
static bool isLegalVotes(int votes);
/**
* getAreaIndexById: Gets the index of the area in the array of areas in a given election
*
* @param election - The to search in
* @param id       - The ID of the area searched
* @return
* 	Index of the area in the array of areas.
*   AREA_NOT_FOUND if the area doesn't exist.
*/
static int getAreaIndexById(Election election, int id);
/**
* multiplyAreasSize: realloc the size of area - multiply it by 2
*
* @param election - the election to enlarge it's area size
* @return
* 	false if allocation falied
*   true if allocation succeeded
*/
static bool multiplyAreasSize(Election election);
/**
* electionChangeVote: will perform the same function for add/remove votes, with
* regard to whether it is adding or removing
*
* @param election - the election to change votes to
* @param area_id - the area_id from which to add/remove votes
* @param tribe_id - the tribe_id to add/remove votes to
* @param num_of_votes - number of votes to add or remove, must be non-negative
* @param add_operation - whether this is a add/remove operation
* @return
* 	Same as electionAddVote & electionRemoveVote
*/
static ElectionResult electionChangeVote(Election election, int area_id, int tribe_id, int num_of_votes, bool add_operation);
/**
* shiftElementsLeft: shift all area elements from current index until the end one place left
*
* @param election - the election to move area elements to 
* @param current_index - where to start to move left the elements
* @return
* 	nothing - void function
*/
static void shiftElementsLeft(Election election, int current_index);
/**
* initializeTribesToArea: when creating new area - initialize all tribe votes to 0
*
* @param area - area to initialize tribes votes from 
* @param tribes - the map of tribes - to check current tribes
* @return
* 	MAP_OUT_OF_MEMORY -  if allocation falied
*   MAP_SUCCESS - if the functions succeeded initialize all tribe votes to 0
*/
static MapResult initializeTribesToArea(Area area, Map tribes);

/**
* checkElectionInput: check the attributes for invalid values or NULL
*
* @param election - the election to check
* @param id - the id to check
* @param name - the name to check
* @param name_dont_care - whether to discard name check or no. True will discard the check.
* @return
* 	ELECTION_NULL_ARGUMENT -  if election is NULL
*   ELECTION_INVALID_ID - if ID is invalid
*   ELECTION_SUCCESS - if all attributes are OK
*/
static inline ElectionResult checkElectionInput(Election election,int id, const char *name,bool name_dont_care);


Election electionCreate()
{
    Election new_election = malloc(sizeof(*new_election));
    RETURN_ON_NULL(new_election, NULL); // check if new_election in NULL and return NULL if so

    new_election->tribes = NULL;
    new_election->areas = NULL;
    new_election->area_count = 0; // initial all attributes to be null or 0 accordingly
    new_election->allocated_size = AREA_INITIAL_SIZE;

    new_election->tribes = mapCreate(); // create Map tribes
    EXECUTE_ON_CONDITION(new_election->tribes, NULL, electionDestroy(new_election), NULL);
    new_election->areas = malloc(sizeof(*new_election->areas) * AREA_INITIAL_SIZE); // create an array of areas
    EXECUTE_ON_CONDITION(new_election->areas, NULL, electionDestroy(new_election), NULL);

    for (int x = 0; x < new_election->allocated_size; x++)
    {
        new_election->areas[x] = NULL;
    }

    return new_election;
}

void electionDestroy(Election election)
{

    RETURN_ON_CONDITION_NO_VALUE(election, NULL);
    mapDestroy(election->tribes);
    areasDestroy(election);
    free(election);
}
ElectionResult electionAddTribe(Election election, int tribe_id, const char *tribe_name)
{
    ElectionResult result = checkElectionInput(election,tribe_id, tribe_name,false);
    RETURN_ON_NOT_CONDITION(result, ELECTION_SUCCESS, result);

    char *tribe_id_str = intToString(tribe_id); // create the char* for the mapGet function
    RETURN_ON_NULL(tribe_id_str, ELECTION_OUT_OF_MEMORY);
    EXECUTE_ON_NOT_CONDITION(mapGet(election->tribes, tribe_id_str), NULL, free(tribe_id_str), ELECTION_TRIBE_ALREADY_EXIST);
    EXECUTE_ON_CONDITION(isLegalName(tribe_name), false, free(tribe_id_str), ELECTION_INVALID_NAME);
    MapResult put_result = mapPut(election->tribes, tribe_id_str, tribe_name); //add the new tribe
    ElectionResult result_to_return = (put_result == MAP_OUT_OF_MEMORY ? ELECTION_OUT_OF_MEMORY : ELECTION_SUCCESS);
    // add to all exsisting areas the new tribe with 0 votes if fails delete all votes of that tribe
    for (int i = 0; i < election->area_count; i++)
    {
        if (areaChangeVotesToTribe(election->areas[i], tribe_id_str, EMPTY) == AREA_OUT_OF_MEMORY)
        {
            electionRemoveTribe(election, tribe_id);
            free(tribe_id_str);
            return ELECTION_OUT_OF_MEMORY;
        }
    }
    free(tribe_id_str); // free the string after usage
    return result_to_return;
}

ElectionResult electionAddArea(Election election, int area_id, const char *area_name)
{
    ElectionResult result = checkElectionInput(election,area_id, area_name,false);
    RETURN_ON_NOT_CONDITION(result, ELECTION_SUCCESS, result);

    if (getAreaIndexById(election, area_id) != AREA_NOT_FOUND)
    {
        return ELECTION_AREA_ALREADY_EXIST;
    }
    // Area doesn't exist
    RETURN_ON_NULL(isLegalName(area_name), ELECTION_INVALID_NAME);
    if (election->area_count == election->allocated_size)
    {
        RETURN_ON_CONDITION(multiplyAreasSize(election), false, ELECTION_OUT_OF_MEMORY); // Wasn't able to allocate more space
        // Will not destroy the original areas array
    }

    Area new_area = areaCreate(area_id, area_name);
    RETURN_ON_NULL(new_area, ELECTION_OUT_OF_MEMORY);

    EXECUTE_ON_CONDITION(initializeTribesToArea(new_area, election->tribes), MAP_OUT_OF_MEMORY, areaDestroy(new_area), ELECTION_OUT_OF_MEMORY);

    election->areas[election->area_count] = new_area;
    election->area_count++;
    return ELECTION_SUCCESS;
}

char *electionGetTribeName(Election election, int tribe_id)
{
    ElectionResult result = checkElectionInput(election,tribe_id, NULL,true);
    RETURN_ON_NOT_CONDITION(result, ELECTION_SUCCESS, NULL);

    char *string_of_tribe_id = intToString(tribe_id);   // create the char* for the mapGet function
    RETURN_ON_NULL(string_of_tribe_id, NULL);           // check if allocation of string_of_int failed
    char *tribe_name = getCopyOfString(mapGet(election->tribes, string_of_tribe_id)); // check if tribe_id exsists
    free(string_of_tribe_id);

    return tribe_name;// if tribe_name remained NULL, then it didn't exist or allocation failure, thus NULL will be returned
}
ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    return electionChangeVote(election, area_id, tribe_id, num_of_votes, true);
}
ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    return electionChangeVote(election, area_id, tribe_id, num_of_votes, false);
}
ElectionResult electionSetTribeName(Election election, int tribe_id, const char *tribe_name)
{
    ElectionResult result = checkElectionInput(election,tribe_id, tribe_name,false);
    RETURN_ON_NOT_CONDITION(result, ELECTION_SUCCESS, result);

    char *tribe_id_str = intToString(tribe_id);
    RETURN_ON_NULL(tribe_id_str, ELECTION_OUT_OF_MEMORY);
    EXECUTE_ON_CONDITION(mapContains(election->tribes, tribe_id_str), false, free(tribe_id_str), ELECTION_TRIBE_NOT_EXIST);
    EXECUTE_ON_CONDITION(isLegalName(tribe_name), false, free(tribe_id_str), ELECTION_INVALID_NAME);

    MapResult put_result = mapPut(election->tribes, tribe_id_str, tribe_name);
    EXECUTE_ON_NOT_CONDITION(put_result, MAP_OUT_OF_MEMORY, free(tribe_id_str), ELECTION_SUCCESS);

    // Shouldn't reach here since mapPut gets non-NULL arguements, thus returns SUCCESS or OUT_OF_MEMORY
    free(tribe_id_str);
    return ELECTION_OUT_OF_MEMORY; 
}
ElectionResult electionRemoveTribe(Election election, int tribe_id)
{
    ElectionResult result = checkElectionInput(election,tribe_id, NULL,true);
    RETURN_ON_NOT_CONDITION(result, ELECTION_SUCCESS, result);

    char *tribe_id_str = intToString(tribe_id);
    RETURN_ON_NULL(tribe_id_str, ELECTION_OUT_OF_MEMORY);
    MapResult remove_result = mapRemove(election->tribes, tribe_id_str);

    EXECUTE_ON_CONDITION(remove_result, MAP_ITEM_DOES_NOT_EXIST, free(tribe_id_str), ELECTION_TRIBE_NOT_EXIST);

    for (int i = 0; i < election->area_count; i++)
    {
        areaRemoveTribe(election->areas[i], tribe_id_str);
    }

    free(tribe_id_str);
    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area)
{
    RETURN_ON_NULL(election, ELECTION_NULL_ARGUMENT);
    RETURN_ON_NULL(should_delete_area, ELECTION_NULL_ARGUMENT);
    for (int area_index = 0; area_index < election->area_count;)
    {
        if (should_delete_area(areaGetId(election->areas[area_index])))
        {
            areaDestroy(election->areas[area_index]);
            shiftElementsLeft(election, area_index);
            election->area_count--;
        }
        else
        {
            area_index++;
        }
    }
    return ELECTION_SUCCESS;
}

Map electionComputeAreasToTribesMapping(Election election)
{
    RETURN_ON_NULL(election, NULL);
    Map elections_map = mapCreate();     // Create empty map
    RETURN_ON_NULL(elections_map, NULL); // if null - return NULL
    // Tribes or areas are zero
    RETURN_ON_CONDITION(mapGetSize(election->tribes), EMPTY, elections_map); // if empty -create empty map
    RETURN_ON_CONDITION(mapGetSize(election->tribes), NULL_POINTER, elections_map);
    RETURN_ON_CONDITION(election->area_count, EMPTY, elections_map); // Better to check area_count no?
    //

    for (int index = 0; index < election->area_count; index++)
    {
        char *most_votes_tribe_id = areaGetMostVotesTribe(election->areas[index]);        // get the tribe_id with most votes
        EXECUTE_ON_CONDITION(most_votes_tribe_id, NULL, mapDestroy(elections_map), NULL); // Shouldn't get here since there more than zero tribes

        char *area_id_string = intToString(areaGetId(election->areas[index]));       // get area_id
        EXECUTE_ON_CONDITION(area_id_string, NULL, mapDestroy(elections_map), NULL); // no need to free area_id since it is NULL

        MapResult put_result = mapPut(elections_map, area_id_string, most_votes_tribe_id); // put {area_id : tribe_id} in map
        free(area_id_string);                                                              // No nned for it anymore
        EXECUTE_ON_CONDITION(put_result, MAP_OUT_OF_MEMORY, mapDestroy(elections_map), NULL);
    }
    return elections_map;
}

// Static Helper functions

static int getAreaIndexById(Election election, int id)
{
    for (int i = 0; i < election->area_count; i++)
    {
        if (areaEquals(election->areas[i], id))
        {
            return i;
        }
    }
    return AREA_NOT_FOUND;
}
static bool multiplyAreasSize(Election election)
{
    Area *new_areas = realloc(election->areas, (sizeof(election->areas)) * (election->allocated_size * AREA_MULTIPLIER_SIZE));
    RETURN_ON_NULL(new_areas, false);
    election->areas = new_areas;
    election->allocated_size *= 2;
    return true;
}
static bool isLegalVotes(int votes)
{
    return (votes > 0);
}
static bool isLegalId(int id)
{
    return (id >= 0);
}
static bool isLegalName(const char *name)
{
    int index = 0;

    while (name[index])
    {
        char current_char = name[index];
        if ((!IS_LOWER(current_char)) && (!((current_char) == (LEGAL_DELIMITER))))
        {

            return false;
        }
        index++;
    }

    return true;
}

static ElectionResult electionChangeVote(Election election, int area_id, int tribe_id, int num_of_votes, bool add_operation)
{
    // Will not use checkElectionInput since it is to much handling for a single more arguement
    RETURN_ON_NULL(election, ELECTION_NULL_ARGUMENT);
    RETURN_ON_NULL(isLegalId(area_id), ELECTION_INVALID_ID); 
    RETURN_ON_NULL(isLegalId(tribe_id), ELECTION_INVALID_ID);
    RETURN_ON_NULL(isLegalVotes(num_of_votes), ELECTION_INVALID_VOTES);
    // Arguements are valid

    int area_index = getAreaIndexById(election, area_id);
    RETURN_ON_CONDITION(area_index, AREA_NOT_FOUND, ELECTION_AREA_NOT_EXIST);

    char *tribe_id_str = intToString(tribe_id);
    RETURN_ON_NULL(tribe_id_str, ELECTION_OUT_OF_MEMORY);
    //  const char * constant_tribe_id = tribe_id_str;
    EXECUTE_ON_CONDITION(mapContains(election->tribes, tribe_id_str), false, free(tribe_id_str), ELECTION_TRIBE_NOT_EXIST);

    //Tribe exists
    int votes_change = num_of_votes;
    if (!add_operation)
        votes_change *= -1;
    AreaResult change_result = areaChangeVotesToTribe(election->areas[area_index], tribe_id_str, votes_change);
    EXECUTE_ON_CONDITION(change_result, AREA_SUCCESS, free(tribe_id_str), ELECTION_SUCCESS);
    EXECUTE_ON_CONDITION(change_result, AREA_OUT_OF_MEMORY, free(tribe_id_str), ELECTION_OUT_OF_MEMORY);
    free(tribe_id_str);
    return ELECTION_OUT_OF_MEMORY; // Shouldn't reach here since results will be only SUCCESS or OUT_OF_MEMORY
}
static void areasDestroy(Election election)
{
    RETURN_ON_CONDITION_NO_VALUE(election, NULL);
    for (int i = 0; i < election->area_count; i++)
    {
        areaDestroy(election->areas[i]);
    }
    election->area_count = 0;
    free(election->areas);
}
static void shiftElementsLeft(Election election, int current_index)
{ // Decreases area index

    for (; current_index < election->area_count - 1; current_index++)
    {
        election->areas[current_index] = election->areas[current_index + 1];
    }
    election->areas[current_index] = NULL; // Last element should point to NULL
    return;
}
static MapResult initializeTribesToArea(Area area, Map tribes)
{
    MAP_FOREACH(tribe_id, tribes)
    {
        AreaResult change_result = areaChangeVotesToTribe(area, tribe_id, EMPTY);
        RETURN_ON_CONDITION(change_result, AREA_OUT_OF_MEMORY, MAP_OUT_OF_MEMORY); // Will create tribe with 0 votes or do nothing
    }
    return MAP_SUCCESS;
}
static inline ElectionResult checkElectionInput(Election election,int id, const char *name,bool name_dont_care)
{
    if (!name_dont_care)
    {
        RETURN_ON_NULL(name, ELECTION_NULL_ARGUMENT);
    }

    RETURN_ON_NULL(election, ELECTION_NULL_ARGUMENT);
    RETURN_ON_NULL(isLegalId(id), ELECTION_INVALID_ID);
    return ELECTION_SUCCESS;
}


#ifndef ELECTION_C_
#define ELECTION_C_

#include "../election.h"
#include "../mtm_map/map.h"
#include "area.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "electionUtils.h"

#define AREA_INITIAL_SIZE 1
#define AREA_MULTIPLIER_SIZE 2
#define AREA_NOT_FOUND -1
#define LEGAL_DELIMITER ' '
#define EMPTY 0
#define NULL_EMPTY -1


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
static char * checkTribeExistsAndReturnName(Election election, int tribe_id);
/*
//for debug
bool Todelete_area(int area_id){
    if (area_id%2 == 0){
        return true;
    }
    return false;
}
*/

Election electionCreate() //Shelly
{
    Election new_Election = malloc(sizeof(*new_Election));
    assert(new_Election);
    RETURN_ON_NULL(new_Election, NULL); // check if new_election in NULL and return NULL if so
    new_Election->tribes = mapCreate();// create Map tribes 
    RETURN_ON_NULL(new_Election->tribes, NULL); 
    new_Election->areas = malloc(sizeof(*new_Election->areas)*AREA_INITIAL_SIZE); // create an array of areas
    RETURN_ON_NULL(new_Election->areas, NULL);
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
    RETURN_ON_NULL(election,ELECTION_NULL_ARGUMENT);
    RETURN_ON_NULL(tribe_name,ELECTION_NULL_ARGUMENT);
    RETURN_ON_NULL(isLegalId(tribe_id), ELECTION_INVALID_ID);

    char* tribe_id_str = intToString(tribe_id); // create the char* for the mapGet function
    EXECUTE_ON_CONDITION(tribe_id_str,NULL,free(tribe_id_str),ELECTION_OUT_OF_MEMORY);
    EXECUTE_ON_NOT_CONDITION(mapGet(election->tribes, tribe_id_str), NULL, free(tribe_id_str),ELECTION_TRIBE_ALREADY_EXIST );
    EXECUTE_ON_CONDITION(isLegalName(tribe_name), false ,free(tribe_id_str), ELECTION_INVALID_NAME );
    MapResult put_result = mapPut(election->tribes,tribe_id_str,tribe_name); //add the new tribe
    ElectionResult result_to_return = (put_result == MAP_OUT_OF_MEMORY ? ELECTION_OUT_OF_MEMORY : ELECTION_SUCCESS);
    free(tribe_id_str); // free the string after usage
    return result_to_return; // Placeholder
}

ElectionResult electionAddArea(Election election, int area_id, const char *area_name)
{
     RETURN_ON_NULL(election,ELECTION_NULL_ARGUMENT);
     RETURN_ON_NULL(area_name,ELECTION_NULL_ARGUMENT);
     RETURN_ON_NULL(isLegalId(area_id), ELECTION_INVALID_ID);

    if(getAreaIndexById(election,area_id)!=AREA_NOT_FOUND)
    {
        return ELECTION_AREA_ALREADY_EXIST;
    }
    // Area doesn't exist
     RETURN_ON_NULL(isLegalName(area_name), ELECTION_INVALID_NAME);
     if (election->area_count == election->allocated_size)
     {
         RETURN_ON_NULL(multiplyAreasSize(election),ELECTION_OUT_OF_MEMORY); // Wasn't able to allocate more space
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
    char* tribe_name = checkTribeExistsAndReturnName(election, tribe_id);
    RETURN_ON_CONDITION(tribe_name, NULL, NULL);
    const char* const_tribe_name = tribe_name;
    return const_tribe_name;
}
ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes) // Shai
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(area_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalVotes(num_of_votes), false, ELECTION_INVALID_VOTES);
    // Arguements are valid

    int area_index;
    RETURN_ON_CONDITION(area_index=getAreaIndexById(election,area_id),AREA_NOT_FOUND,ELECTION_AREA_NOT_EXIST);

    char* tribe_id_str = intToString(tribe_id); // Should free!
    DESTROY_ON_CONDITION(tribe_id_str ,NULL ,election,ELECTION_OUT_OF_MEMORY);
    RETURN_ON_CONDITION(mapContains(election->tribes,tribe_id_str),false,ELECTION_TRIBE_NOT_EXIST);
    //Tribe exists
    AreaResult change_result =areaChangeVotesToTribe(election->areas[area_index],tribe_id_str,num_of_votes);
    RETURN_ON_CONDITION(change_result,AREA_SUCCESS,ELECTION_SUCCESS);
     DESTROY_ON_CONDITION(change_result,AREA_OUT_OF_MEMORY,election,ELECTION_OUT_OF_MEMORY);
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

    char * string_tribe_id = intToString(tribe_id);
    DESTROY_ON_CONDITION(string_tribe_id ,NULL ,election,ELECTION_OUT_OF_MEMORY);
    const char * const_tribe_id = string_tribe_id;
    AreaResult change_result =areaChangeVotesToTribe(election->areas[area_index], const_tribe_id, 0-num_of_votes); 
    DESTROY_ON_CONDITION(change_result,AREA_OUT_OF_MEMORY,election,ELECTION_OUT_OF_MEMORY)
    
    return ELECTION_SUCCESS; // Placeholder
}
ElectionResult electionSetTribeName(Election election, int tribe_id, const char *tribe_name) // Shai
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(tribe_name,NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
  const char* tribe_id_str;
   DESTROY_ON_CONDITION(tribe_id_str =intToString(tribe_id),NULL,election,ELECTION_OUT_OF_MEMORY);
    RETURN_ON_CONDITION(mapContains(election->tribes,tribe_id_str),false,ELECTION_TRIBE_NOT_EXIST);
    RETURN_ON_CONDITION(isLegalName(tribe_name), false, ELECTION_INVALID_NAME);

MapResult put_result = mapPut(election->tribes,tribe_id_str,tribe_name);
    RETURN_ON_CONDITION(put_result,MAP_SUCCESS,ELECTION_SUCCESS);
    DESTROY_ON_CONDITION(put_result,MAP_OUT_OF_MEMORY,election,ELECTION_OUT_OF_MEMORY);

// Shouldn't reach here since mapPut gets non-NULL arguements, thus returns SUCCESS or OUT_OF_MEMORY
    return ELECTION_SUCCESS;
}
ElectionResult electionRemoveTribe(Election election, int tribe_id) // Shai
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
  const char* tribe_id_str;
    DESTROY_ON_CONDITION(tribe_id_str =intToString(tribe_id),NULL,election,ELECTION_OUT_OF_MEMORY);
   
   //Remove from tribes map:
   MapResult remove_result = mapRemove(election->tribes,tribe_id_str);

    RETURN_ON_CONDITION(remove_result,MAP_ITEM_DOES_NOT_EXIST,ELECTION_TRIBE_NOT_EXIST);
    
    for (int i = 0; i < election->area_count; i++)
    {
        areaRemoveTribe(election->areas[i],tribe_id_str);
    }
    

    return ELECTION_SUCCESS;
}
static void promoteEachElementAfter(Election election, int current_index){
    for (int area_index = current_index; area_index < election->area_count -1; area_index ++){
        election->areas[area_index] = election->areas[area_index+1]; 
    }
    return;
}
ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area) //Shelly
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(should_delete_area, NULL,ELECTION_NULL_ARGUMENT);
    for (int area_index = 0; area_index < election->area_count;){
        if (should_delete_area(areaGetId(election->areas[area_index]))){
            areaDestroy(election->areas[area_index]);
            promoteEachElementAfter(election, area_index);
            election->area_count --;
        }
        else{
            area_index ++;
        }   
    }
    return ELECTION_SUCCESS; // Placeholder
}

Map electionComputeAreasToTribesMapping(Election election) // UNITED!
{
    Map elections_map = mapCreate(); // Create empty map
    RETURN_ON_CONDITION(election, NULL, NULL); // if null - return NULL
    RETURN_ON_CONDITION(mapGetSize(election->tribes), EMPTY, elections_map);// if empty -create empty map
    RETURN_ON_CONDITION(mapGetSize(election->tribes), NULL_EMPTY, elections_map);
    
    RETURN_ON_CONDITION(election->area_count, EMPTY, elections_map);// Better to check area_count no?
    
    for(int index = 0; index < election->area_count; index ++){
        const char * most_votes_tribe_id = areaGetMostVotesTribe(election->areas[index]); // get the tribe_id with most votes
        RETURN_ON_CONDITION(most_votes_tribe_id, NULL,NULL);
        char * area_id_string = intToString(areaGetId(election->areas[index])); // get area_id
        RETURN_ON_CONDITION(area_id_string, NULL,NULL);
        const char * const_area_id = area_id_string; // turn area_id to const char
        MapResult put_result= mapPut(elections_map, const_area_id,most_votes_tribe_id ); // put {area_id : tribe_id} in map
        RETURN_ON_CONDITION(put_result,MAP_OUT_OF_MEMORY,NULL); // Should check result
    }
    return elections_map; 
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
    realloc(election->areas,(sizeof( election->areas))*(election->allocated_size*AREA_MULTIPLIER_SIZE));
    RETURN_ON_NULL(election->areas,false);
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

//    char* temp_str =malloc(strlen(name) +1) ;

    int index=0;

   while (name[index])
   {
         char current_char = name[index];
        if((!IS_LOWER(current_char) )&& (!((current_char)==(LEGAL_DELIMITER ))))
        {
           
            return false;
        }
        index++;

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

static void areasDestroy(Election election)
{
    RETURN_ON_CONDITION_NO_VALUE(election, NULL);
    for (int i = 0; i < election->area_count; i++)
    {
        areaDestroy(election->areas[i]);
    }
    free(election->areas);
}
static char *checkTribeExistsAndReturnName(Election election, int tribe_id)
{
    char *string_of_tribe_id = intToString(tribe_id);                      // create the char* for the mapGet function
    RETURN_ON_CONDITION(string_of_tribe_id, NULL, ELECTION_OUT_OF_MEMORY); // check if allocation of string_of_int failed
    const char *const_string_of_tribe_id = string_of_tribe_id;             // convert char to const char
    char *tribe_name = mapGet(election->tribes, const_string_of_tribe_id); // check if tribe_id exsists
    free(string_of_tribe_id);
    return tribe_name; // return Tribe name or NULL if the tribe doesnt exists
}
//for gebug
int main()
{
   
   // bool (*ptr)(int) = NULL;
   // ptr = Todelete_area;
    Election elec =electionCreate();
    electionAddArea(elec,1234,"winterfell");
   //   electionAddArea(elec,1234,"kings landing");
    electionAddArea(elec,12,"kings landing");
    electionAddTribe(elec, 676, "voodoo");
    electionAddTribe(elec, 350, "popo");
    electionAddVote(elec, 12, 676, 10);
    electionAddVote(elec, 12, 350, 20);
    electionAddVote(elec, 1234, 350, 30);
    //electionRemoveTribe(elec, 350);
    //electionAddTribe(elec, 350, "popo");
    //electionRemoveVote(elec, 12, 676, 6); // Maybe also bug here
     // electionSetTribeName(elec, 6766, "power");
    electionComputeAreasToTribesMapping(elec);
      electionDestroy(elec);
}

#endif //ELECTION_C_
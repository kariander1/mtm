
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
#include "area.c"
#include "../mtm_map/map.c"
#include "electionUtils.c"

#define AREA_INITIAL_SIZE 1
#define AREA_MULTIPLIER_SIZE 2
#define AREA_NOT_FOUND -1
#define LEGAL_DELIMITER ' '
#define EMPTY 0
# define NULL_POINTER -1


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
static char * checkTribeExsistsAndReturnName(Election election, int tribe_id);
static void promoteEachElementAfter(Election election, int current_index);
//for debug
bool Todelete_area(int area_id){
    if (area_id%2 == 0){
        return true;
    }
    return false;
}


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
    char* string_of_tribe_id = intToString(tribe_id); // create the char* for the mapGet function
    if (string_of_tribe_id == NULL){
        free(string_of_tribe_id);
        electionDestroy(election);
        return  ELECTION_OUT_OF_MEMORY;
    }
    const char * constant_string_of_tribe_id = string_of_tribe_id;
    EXECUTE_ON_NOT_CONDITION(mapGet(election->tribes, constant_string_of_tribe_id), NULL, free(string_of_tribe_id),ELECTION_TRIBE_ALREADY_EXIST );
    EXECUTE_ON_CONDITION(isLegalName(tribe_name), false ,free(string_of_tribe_id), ELECTION_INVALID_NAME );
    mapPut(election->tribes,constant_string_of_tribe_id,tribe_name); //add the new tribe
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
    const char* constant_tribe_name = tribe_name;
    return constant_tribe_name;
}
ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(area_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    RETURN_ON_CONDITION(isLegalVotes(num_of_votes), false, ELECTION_INVALID_VOTES);
    // Arguements are valid

    int area_index;
    RETURN_ON_CONDITION(area_index=getAreaIndexById(election,area_id),AREA_NOT_FOUND,ELECTION_AREA_NOT_EXIST);

    char* tribe_id_str = intToString(tribe_id); 
    DESTROY_ON_CONDITION(tribe_id_str ,NULL ,election,ELECTION_OUT_OF_MEMORY);
    const char * constant_tribe_id = tribe_id_str;
    EXECUTE_ON_CONDITION(mapContains(election->tribes,constant_tribe_id),false, free(tribe_id_str), ELECTION_TRIBE_NOT_EXIST);
    //Tribe exists
    EXECUTE_ON_CONDITION(areaChangeVotesToTribe(election->areas[area_index],constant_tribe_id,num_of_votes),AREA_SUCCESS, free(tribe_id_str),ELECTION_SUCCESS); //don't you need to set as const char?------
    free(tribe_id_str);
    return ELECTION_OUT_OF_MEMORY; //Maybe?
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
    DESTROY_ON_CONDITION(string_tribe_id ,NULL ,election,ELECTION_OUT_OF_MEMORY); // dont need to free string_tribe_id
    const char * constant_tribe_id = string_tribe_id;
     if (areaChangeVotesToTribe(election->areas[area_index], constant_tribe_id, 0-num_of_votes) != AREA_SUCCESS){
        free(string_tribe_id);
        electionDestroy(election);
        return ELECTION_OUT_OF_MEMORY;
    }
    //DESTROY_ON_CONDITION(areaChangeVotesToTribe(election->areas[area_index], const_tribe_id, 0-num_of_votes),ELECTION_OUT_OF_MEMORY,election,ELECTION_OUT_OF_MEMORY)
    free(string_tribe_id);
    return ELECTION_SUCCESS; // Placeholder
}
ElectionResult electionSetTribeName(Election election, int tribe_id, const char *tribe_name) // Shai
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(tribe_name,NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    char* tribe_id_str;
    DESTROY_ON_CONDITION(tribe_id_str =intToString(tribe_id),NULL,election,ELECTION_OUT_OF_MEMORY);
    const char * constant_tribe_id = tribe_id_str;
    EXECUTE_ON_CONDITION(mapContains(election->tribes,constant_tribe_id), false, free(tribe_id_str),ELECTION_TRIBE_NOT_EXIST);
    //RETURN_ON_CONDITION(mapContains(election->tribes,constant_tribe_id),false,ELECTION_TRIBE_NOT_EXIST);
    EXECUTE_ON_CONDITION(isLegalName(tribe_name), false, free(tribe_id_str) ,ELECTION_INVALID_NAME);

    MapResult put_result = mapPut(election->tribes,constant_tribe_id,tribe_name);
    EXECUTE_ON_CONDITION(put_result,MAP_SUCCESS, free(tribe_id_str),ELECTION_SUCCESS);
    //DESTROY_ON_CONDITION(put_result,MAP_OUT_OF_MEMORY,election,ELECTION_OUT_OF_MEMORY);
    if (put_result == MAP_OUT_OF_MEMORY){
        free(tribe_id_str);
        electionDestroy(election);
        return ELECTION_OUT_OF_MEMORY;
    }
// Shouldn't reach here since mapPut gets non-NULL arguements, thus returns SUCCESS or OUT_OF_MEMORY
    
    return ELECTION_SUCCESS;
}
ElectionResult electionRemoveTribe(Election election, int tribe_id)
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(isLegalId(tribe_id), false, ELECTION_INVALID_ID);
    char* tribe_id_str;
    DESTROY_ON_CONDITION(tribe_id_str =intToString(tribe_id),NULL,election,ELECTION_OUT_OF_MEMORY);
    const char * constant_tribe_id = tribe_id_str;
   //Remove from tribes map:
    MapResult remove_result = mapRemove(election->tribes,constant_tribe_id);
    EXECUTE_ON_CONDITION(remove_result,MAP_ITEM_DOES_NOT_EXIST, free(tribe_id_str),ELECTION_TRIBE_NOT_EXIST);
    
    for (int i = 0; i < election->area_count; i++)
    {
        areaRemoveTribe(election->areas[i],constant_tribe_id);
    }
    
    free(tribe_id_str);
    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area) //Shelly
{
    RETURN_ON_CONDITION(election, NULL,ELECTION_NULL_ARGUMENT);
    RETURN_ON_CONDITION(should_delete_area, NULL,ELECTION_NULL_ARGUMENT);
    for (int area_index = 0; area_index < election->area_count;){
        if (should_delete_area(election->areas[area_index]->area_id)){
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
    RETURN_ON_CONDITION(election, NULL, NULL); // if null - return NULL
    RETURN_ON_CONDITION(mapGetSize(election->tribes), NULL_POINTER, mapCreate()); // if a null pointer was sent
    RETURN_ON_CONDITION(mapGetSize(election->tribes), EMPTY, mapCreate());// if empty -create empty map
    RETURN_ON_CONDITION(*(election->areas), NULL, mapCreate());// if null -create empty map
    Map elections_map = mapCreate();
    char * area_id_string;
    for(int index = 0; index < election->area_count; index ++){
        const char * most_votes_tribe_id = areaGetMostVotesTribe(election->areas[index]); // get the tribe_id with most votes
        EXECUTE_ON_CONDITION(most_votes_tribe_id, NULL, mapDestroy(elections_map),NULL);
        area_id_string = intToString(election->areas[index]->area_id); // get area_id - NEED TO CHANGE
        EXECUTE_ON_CONDITION(area_id_string, NULL, mapDestroy(elections_map),NULL);
        const char * constant_area_id = area_id_string; // turn area_id to const char
        if (mapPut(elections_map, constant_area_id,most_votes_tribe_id ) !=MAP_SUCCESS ){ // put {area_id : tribe_id} in map
             free(area_id_string);
             mapDestroy(elections_map);
             return NULL;
        }
        //EXECUTE_ON_NOT_CONDITION(mapPut(elections_map, const_area_id,most_votes_tribe_id ), MAP_SUCCESS, free(area_id_string), elections_map );
        //mapPut(elections_map, const_area_id,most_votes_tribe_id ); 
    }
    free(area_id_string);
    return elections_map; // Placeholder
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
    char* string_of_tribe_id = intToString(tribe_id); // create the char* for the mapGet function
    RETURN_ON_CONDITION(string_of_tribe_id, NULL,ELECTION_OUT_OF_MEMORY );// check if allocation of string_of_int failed
    const char * constant_string_of_tribe_id = string_of_tribe_id; // convert char to const char 
    char* tribe_name = mapGet(election->tribes, constant_string_of_tribe_id); // check if tribe_id exsists
    free(string_of_tribe_id);
    return tribe_name; // return Tribe name or NULL if the tribe doesnt exsists
}
static void promoteEachElementAfter(Election election, int current_index){ // promotes the area index
    for (int area_index = current_index; area_index < election->area_count -1; area_index ++){
        election->areas[area_index] = election->areas[area_index+1]; 
    }
    return;
}
//for gebug
int main()
{
    bool (*ptr)(int) = NULL;
    ptr = Todelete_area;
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
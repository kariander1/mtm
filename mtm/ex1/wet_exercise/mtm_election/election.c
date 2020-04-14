
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
    RETURN_ON_CONDITION(string_of_tribe_id, NULL,ELECTION_OUT_OF_MEMORY );// check if allocation of string_of_int failed
    const char * const_string_of_tribe_id = string_of_tribe_id;
     // free the string after usage// should be freed here, if later, the program might return wthout freeing

    if (mapGet(election->tribes, const_string_of_tribe_id) != NULL){
        free(string_of_tribe_id);
        return ELECTION_TRIBE_ALREADY_EXIST; // Should be EXIST_ALREADY_TRIBE_ELECTION?
    }
    //RETURN_ON_CONDITION(mapGet(election->tribes, const_string_of_tribe_id), (!NULL), ELECTION_INVALID_ID); // check if tribe_id exsists
    EXECUTE_ON_CONDITION(isLegalName(tribe_name), false,free(string_of_tribe_id), ELECTION_INVALID_NAME);
    EXECUTE_ON_CONDITION(mapPut(election->tribes,const_string_of_tribe_id,tribe_name),MAP_SUCCESS,     free(string_of_tribe_id),ELECTION_SUCCESS); //add the new tribe // should check for errors!
    // If reached here, something went wrong
     free(string_of_tribe_id);
    
    electionDestroy(election);
    return ELECTION_OUT_OF_MEMORY; // Placeholder
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
    // Arguements are valid

    int area_index;
    RETURN_ON_CONDITION(area_index=getAreaIndexById(election,area_id),AREA_NOT_FOUND,ELECTION_AREA_NOT_EXIST);
    // Area exists
    const char* tribe_id_str;
    DESTROY_ON_CONDITION(tribe_id_str =intToString(tribe_id),NULL,election,ELECTION_OUT_OF_MEMORY);
    RETURN_ON_CONDITION(mapContains(election->tribes,tribe_id_str),false,ELECTION_TRIBE_NOT_EXIST);
    //Tribe exists
    RETURN_ON_CONDITION(areaChangeVotesToTribe(election->areas[area_index],tribe_id_str,num_of_votes),AREA_SUCCESS,ELECTION_SUCCESS);
    
    return ELECTION_OUT_OF_MEMORY; //Maybe?
}
ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes) // Shelly
{

    // You can use getAreaIndexById function
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
    const char * const_string_of_tribe_id = string_of_tribe_id; // convert char to const char 
    char* tribe_name = mapGet(election->tribes, const_string_of_tribe_id); // check if tribe_id exsists
    free(string_of_tribe_id);
    return tribe_name; // return Tribe name or NULL if the tribe doesnt exsists
}
//for gebug
int main()
{
    Election elec =electionCreate();
    electionAddArea(elec,1234,"winterfell");
      electionAddArea(elec,1234,"kings landing");
      electionAddArea(elec,12,"kings landing");
      electionAddTribe(elec,676,"voodoo");
      electionAddVote(elec,12,676,10);
      electionSetTribeName(elec,6766,"power");
    electionDestroy(elec);
}

#endif //ELECTION_C_
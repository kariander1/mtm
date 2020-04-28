#include "election.h"
#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define INITIAL_SIZE 4

static char* intToCharPtr(int num);
static ElectionResult checkForErrors(Election election, const char* name1, const char* name2, char* id1, char* id2, bool check_e1, bool check_ne1, bool check_e2, bool check_ne2);
static bool isValidName(const char* name);
static ElectionResult changeNumberOfVotes(Election election, int area_id, int tribe_id, int num_of_votes, bool toAdd);


struct votes_t
{
    char *area_id;
    Map votes_for_tribe;
};
typedef struct votes_t* VotersFromArea;

struct election_t
{
    Map tribes;
    Map areas; 
    int max_num_of_areas;
    VotersFromArea *voters_from_area;
};

Election electionCreate()
{
    Election election = malloc(sizeof(*election));
    if (election == NULL){
        return NULL;
    }
    election->tribes = mapCreate();
    if (election->tribes==NULL){
        free(election);
        return NULL;
    }
    election->areas = mapCreate();
    if (election->areas==NULL){
        free(election);
        mapDestroy(election->tribes);
        return NULL;
    }    
    election->voters_from_area = malloc(INITIAL_SIZE*sizeof(VotersFromArea));

    for(int i=0; i<INITIAL_SIZE; i++){
        election->voters_from_area[i] = malloc(sizeof(VotersFromArea));
        if (election->voters_from_area==NULL){
            free(election);
            mapDestroy(election->tribes);
            mapDestroy(election->areas);
            for(int j=0; j<i; j++){
                free(election->voters_from_area[j]);
            }
            return NULL;
        }    
    }
    for(int i=0; i<INITIAL_SIZE; i++){
        election->voters_from_area[i]->votes_for_tribe = mapCreate();
        if ((election->voters_from_area+i)==NULL){
            for(int j=0; j<i;j+=2){
                free(election->voters_from_area[i]);
            }
            free(election);
            mapDestroy(election->tribes);
            mapDestroy(election->areas);
            free(election->voters_from_area);
            return NULL;
        }
    }
    election->max_num_of_areas=INITIAL_SIZE;
    return election;
}

void electionDestroy(Election election)
{
    int size = INITIAL_SIZE;
    if(mapGetSize(election->areas)>size){
        size = mapGetSize(election->areas);
    }
    for(int i=0; i<size; i++){
        mapDestroy(election->voters_from_area[i]->votes_for_tribe);
        free(election->voters_from_area[i]);;
    }
    mapDestroy(election->tribes);
    mapDestroy(election->areas);   
    free(election); 
}

ElectionResult electionAddTribe(Election election, int tribe_id, const char* tribe_name)
{
    char* id;
    id = NULL; //Shai Test 
    if(checkForErrors(election, tribe_name, tribe_name, id, id, 0,0,0,0)!=ELECTION_SUCCESS){
        return checkForErrors(election, tribe_name, tribe_name, id, id,0,0,0,0);
    }
    if(mapPut(election->tribes, id, tribe_name)==MAP_OUT_OF_MEMORY){
        return ELECTION_OUT_OF_MEMORY;
    }
    for(int i=0; i<mapGetSize(election->areas); i++){
        if(mapPut(election->voters_from_area[i]->votes_for_tribe, id, 0 )==MAP_OUT_OF_MEMORY){
            return ELECTION_OUT_OF_MEMORY;
        }
    }
    return ELECTION_SUCCESS;
}

ElectionResult electionAddArea(Election election, int area_id, const char* area_name)
{
    char* id;
    id = NULL; //Shai test
    if(checkForErrors(election, area_name, area_name, id, id, 1,0,0,0)!=ELECTION_SUCCESS){
        return checkForErrors(election, area_name,area_name, id, id,1,0,0,0);
    }
    if(mapPut(election->areas, id, area_name)==MAP_OUT_OF_MEMORY){
        return ELECTION_OUT_OF_MEMORY;
    }
    /*   need to figure out how to deal with that...
    if(election->num_of_areas > election->max_num_of_areas) {
        
    }
    */
    election->voters_from_area[mapGetSize(election->areas)]->area_id = id;
    return ELECTION_SUCCESS;
}

char* electionGetTribeName(Election election, int tribe_id)
{
    char* id;
    id = NULL; //Shai Test
    if(election==NULL || (mapGet(election->tribes,id)==NULL)){
        return NULL;
    }
    char* the_tribe = malloc(sizeof(char*));
    if(the_tribe==NULL){
        return NULL;
    }
    the_tribe = mapGet(election->tribes,id);
    return the_tribe;
}

ElectionResult electionSetTribeName (Election election, int tribe_id, const char* tribe_name)
{
    char* id;
    id = NULL; //Shai Test
    if(checkForErrors(election, tribe_name, tribe_name, id, id,0,0,0,1)!=ELECTION_SUCCESS){
        return checkForErrors(election, tribe_name,tribe_name, id, id,0,0,0,1);
    }
    if(mapPut(election->tribes, id, tribe_name)==MAP_OUT_OF_MEMORY){
        return ELECTION_OUT_OF_MEMORY;
    }
    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveTribe(Election election, int tribe_id)
{
    char* id;
    id = NULL; //Shai Test
    if(checkForErrors(election, "a", "a", id, id,0,0,0,1)!=ELECTION_SUCCESS){
        return checkForErrors(election, "a","a", id, id,0,0,0,1);
    }
    mapRemove(election->tribes, id);
    for(int i=0; i<mapGetSize(election->areas); i++){
        mapRemove(election->voters_from_area[i]->votes_for_tribe, id);
    }
    return ELECTION_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////
ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area)
{
    return ELECTION_NULL_ARGUMENT; // Placeholder by Shai
}
//////////////////////////////////////////////////////////////////////////////////////

ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    return changeNumberOfVotes(election, area_id, tribe_id, num_of_votes, true);
}

ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    return changeNumberOfVotes(election, area_id, tribe_id, num_of_votes, false);
}

Map electionComputeAreasToTribesMapping(Election election)
{
    if(election == NULL){
        return NULL;
    }
    Map the_results = mapCreate();
    if(the_results==NULL){
        return NULL;
    }
    for(int i=0; i<mapGetSize(election->areas); i++){
        char* current_tribe = mapGetFirst(election->voters_from_area[i]->votes_for_tribe);
        int max_num_of_votes = (int) *mapGet(election->voters_from_area[i]->votes_for_tribe, current_tribe);
        char* current_area;
        current_area = election->voters_from_area[i]->area_id;
        for(int j=0; j<mapGetSize(election->tribes); j++){
            char* next_tribe = mapGetNext(election->voters_from_area[i]->votes_for_tribe);
            if((int) *mapGet(election->voters_from_area[i]->votes_for_tribe, next_tribe) > max_num_of_votes){
                current_tribe = next_tribe;
                max_num_of_votes = (int) *mapGet(election->voters_from_area[i]->votes_for_tribe, next_tribe);
            }
        }
        if(mapPut(the_results, current_area, current_tribe)!=MAP_SUCCESS){
            return NULL;
        }
    }
    return the_results;
}

/////////////////////////local helper functions///////////////////////////

static ElectionResult checkForErrors(Election election, const char* name1, const char* name2, char* id1, char* id2, bool check_e1, bool check_ne1, bool check_e2, bool check_ne2)
{
    if(election == NULL || name1 == NULL || name2 == NULL){
        return ELECTION_NULL_ARGUMENT;
    }
    /*
    if(id1<0||id2<0){
        return ELECTION_INVALID_ID;
    }*/
    if ((!isValidName(name1))||(!isValidName(name2))){
        return ELECTION_INVALID_NAME;
    }
    //1-areas 2-tribes//
    if(check_e1){
        if(mapContains(election->areas, id1)){
            return ELECTION_AREA_ALREADY_EXIST;
        }
    }
    if(check_ne1){
        if(!mapContains(election->areas, id1)){
            return ELECTION_AREA_NOT_EXIST;
        }
    }
    if(check_e2){
        if(mapContains(election->tribes, id2)){
            return ELECTION_TRIBE_ALREADY_EXIST;
        }
    }
    if(check_ne2){
        if(mapContains(election->tribes, id2)){
            return ELECTION_TRIBE_NOT_EXIST;
        }
    }
    return ELECTION_SUCCESS;
}

static bool isValidName(const char* name)
{
    for (int i=0; name[i]!='\0';i++){
        if((name[i]>'a'&& name[i]!=' ')||(name[i]>'z')){
            return false;
        }
    }
    return true;
}

static ElectionResult changeNumberOfVotes(Election election, int area_id, int tribe_id, int num_of_votes, bool toAdd)
{

    if (checkForErrors(election, "a","a",intToCharPtr(area_id),intToCharPtr(tribe_id),0,0,1,1)!=ELECTION_SUCCESS){
        return checkForErrors(election, "a","a",intToCharPtr(area_id),intToCharPtr(tribe_id),0,0,1,1);
    }
    if(!(num_of_votes>0)){
        return ELECTION_INVALID_VOTES;
    }
    char* votes_number = intToCharPtr(num_of_votes);
    if(!toAdd){
        *votes_number = (-(*votes_number));
    }
    int index=0;
    for(index=0; index<mapGetSize(election->areas); index++){
        if(*election->voters_from_area[index]->area_id == (char)area_id){
            break;
        }
    }
    mapPut(election->voters_from_area[index]->votes_for_tribe, intToCharPtr(area_id), votes_number);
    if(!toAdd){
        int current_votes = (int) *mapGet(election->voters_from_area[index]->votes_for_tribe, intToCharPtr(tribe_id));
        if(current_votes<0){
            mapPut(election->voters_from_area[index]->votes_for_tribe, intToCharPtr(tribe_id), 0);
        }
    }
    return ELECTION_SUCCESS;
}

static char* intToCharPtr(int num)
{
   // char* num_ptr;
  //  *num_ptr = (char)num;

    return NULL; // Place holder by Shai
}
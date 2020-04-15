#ifndef AREA_C_
#define AREA_C_

#include "area.h"
#include "../mtm_map/map.h"
#include <stdlib.h>
#include "electionUtils.h"
struct area_t
{
    int area_id;
    const char* area_name;
    Map votes;
};

/* FUNCTUIONS REGARDING AREA:
- areaClear(Area area)
- areaCreate()
- areaDestroy(Area area)
- areaChangeNumOfVotes(Area area, tribe_id, +-num_of_votes);
*/

Area areaCreate(int area_id,const char* area_name)
{
    Area new_area = malloc(sizeof(*new_area));
    RETURN_ON_NULL(new_area,NULL);

    new_area->area_id = area_id;
    new_area->area_name = area_name;

    Map new_map =mapCreate();
       RETURN_ON_NULL(new_map,NULL);
    new_area->votes =new_map;
    return new_area;

}
void areaDestroy(Area area)
{
    if(!area)
    {
        return;
    }
    mapDestroy(area->votes);
    free(area);
}
void areaRemoveTribe(Area area, const char* tribe_id)
{
    RETURN_ON_CONDITION_NO_VALUE(area,NULL);
    RETURN_ON_CONDITION_NO_VALUE(tribe_id,NULL);
    mapRemove(area->votes,tribe_id); // Doesn't matter what is returned, cannot be memory error
}
AreaResult areaChangeVotesToTribe(Area area, const char* tribe_id, int num_of_votes)
{
    RETURN_ON_NULL(area,AREA_NULL_ARGUEMENT);// CHANGE from NULL
    RETURN_ON_NULL(tribe_id,AREA_NULL_ARGUEMENT);
    char* votes_str = mapGet(area->votes,tribe_id);
    int current_votes=0;
    if (votes_str)
    { // Tribe votes exist in votes 
        current_votes = stringToInt(votes_str);
    }
    //Calc new votes
    current_votes+=num_of_votes;
    char* new_votes_str = intToString(current_votes);
  //  const char * new_votes_constant = new_votes_str; // No nneed
    EXECUTE_ON_CONDITION(new_votes_str,NULL, free (new_votes_str), AREA_FAILED_CONVERSION);
    if(mapPut(area->votes,tribe_id,new_votes_str)!=MAP_SUCCESS)
    {
        free (new_votes_str);
        return AREA_OUT_OF_MEMORY;///Find corrent val
    }
    free (new_votes_str);
    return AREA_SUCCESS;

}
bool areaEquals(Area area,int id)
{
    return area->area_id == id;
}
int areaGetId(Area area)
{
    return area->area_id;
}
const char* areaGetMostVotesTribe(Area area){
    RETURN_ON_CONDITION(area, NULL, NULL);
    int max_num_of_votes = 0;
    char *current_tribe = mapGetFirst(area->votes); // returns the key - tribe_id
    char *max_votes_tribe = current_tribe;          // initialize max_votes_tribe

    while (current_tribe)
    {
        const char *const_current_tribe = current_tribe;                       // create const fot tribe_id
        char *current_num_of_votes = mapGet(area->votes, const_current_tribe); // get the number of votes for the current tribe
        int num_of_votes = stringToInt(current_num_of_votes);
        if (num_of_votes > max_num_of_votes)
        {
            max_num_of_votes = num_of_votes;
            max_votes_tribe = current_tribe; // tribe_id
        }
        else if (num_of_votes == max_num_of_votes)
        {
           max_votes_tribe = (stringToInt(max_votes_tribe) < stringToInt(current_tribe) ? max_votes_tribe : current_tribe); // get the tribe with the largest id // Should be lowest
        }
        current_tribe = mapGetNext(area->votes); // promote current tribe
    }

    const char *max_votes_tribe_const = max_votes_tribe;
    return max_votes_tribe_const;
}
//static int stringToInt
#endif // AREA_C
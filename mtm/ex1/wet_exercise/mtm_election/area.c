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


Area areaCreate(int area_id,const char* area_name)
{
    Area new_area = malloc(sizeof(*new_area));
    RETURN_ON_NONEXISTENCE(new_area,NULL);

    new_area->area_id = area_id;
    new_area->area_name = area_name;

    Map new_map =mapCreate();
       RETURN_ON_NONEXISTENCE(new_map,NULL);
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
    RETURN_ON_NONEXISTENCE(area,AREA_NULL_ARGUEMENT);// CHANGE from NULL
    RETURN_ON_NONEXISTENCE(tribe_id,AREA_NULL_ARGUEMENT);
    char* votes_str = mapGet(area->votes,tribe_id);
    int current_votes=0;
    if (votes_str)
    { // Tribe votes exist in votes 
        current_votes = stringToInt(votes_str);
    }
    //Calc new votes
    current_votes+=num_of_votes;
    char* new_votes_str = intToString(num_of_votes);
    RETURN_ON_NONEXISTENCE(new_votes_str,AREA_FAILED_CONVERSION);
    if(mapPut(area->votes,tribe_id,new_votes_str)!=MAP_SUCCESS)
    {
        return AREA_OUT_OF_MEMORY;///Find corrent val
    }

    return AREA_SUCCESS;

}
bool areaEquals(Area area_1,int id)
{
    return area_1->area_id == id;
}

//static int stringToInt
#endif // AREA_C
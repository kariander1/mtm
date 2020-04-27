#ifndef AREA_C_
#define AREA_C_

#include "area.h"
#include "mtm_map/map.h"
#include <stdlib.h>
#include "macro.h"
#include "election_utilities.h"

#define INITIAL_ZERO "0"
struct area_t
{
    int area_id;
    const char *area_name;
    Map votes;
};


Area areaCreate(int area_id, const char *area_name)
{
    Area new_area = malloc(sizeof(*new_area));
    RETURN_ON_NULL(new_area, NULL);

    new_area->area_id = area_id;
    new_area->area_name = area_name;

    Map new_map = mapCreate();
    EXECUTE_ON_CONDITION(new_map,NULL,areaDestroy(new_area),NULL);
    new_area->votes = new_map;
    return new_area;
}
void areaDestroy(Area area)
{
    if (!area)
    {
        return;
    }
    mapDestroy(area->votes);
    free(area);
}

void areaRemoveTribe(Area area, const char *tribe_id)
{
    RETURN_ON_CONDITION_NO_VALUE(area, NULL);
    RETURN_ON_CONDITION_NO_VALUE(tribe_id, NULL);
    mapRemove(area->votes, tribe_id); // Doesn't matter what is returned, cannot be memory error
}

bool areaEquals(Area area, int id)
{
    return area->area_id == id;
}
int areaGetId(Area area)
{
    return area->area_id;
}
char *areaGetMostVotesTribe(Area area)
{
    RETURN_ON_NULL(area, NULL);
    int max_num_of_votes = 0;

    char *max_votes_tribe=NULL;
    MAP_FOREACH(current_tribe, area->votes)
    {
        char *current_num_of_votes = mapGet(area->votes, current_tribe); // get the number of votes for the current tribe
        int num_of_votes = stringToInt(current_num_of_votes);
        if (!max_votes_tribe || (num_of_votes > max_num_of_votes))
        {
            max_num_of_votes = num_of_votes;
            max_votes_tribe = current_tribe; // tribe_id
        }
        else if (num_of_votes == max_num_of_votes)
        {
            max_votes_tribe = (stringToInt(max_votes_tribe) < stringToInt(current_tribe) ? max_votes_tribe : current_tribe); // get the tribe with the largest id // Should be lowest
        }
    }
    return max_votes_tribe;
}
AreaResult areaChangeVotesToTribe(Area area, const char *tribe_id, int num_of_votes)
{
    RETURN_ON_NULL(area, AREA_NULL_ARGUEMENT);
    RETURN_ON_NULL(tribe_id, AREA_NULL_ARGUEMENT);
    char *votes_str = mapGet(area->votes, tribe_id);
    int current_votes = 0;
    if (votes_str)
    { // Tribe votes exist in votes
        current_votes = stringToInt(votes_str);
    }
    //Calc new votes
    current_votes += num_of_votes;
    current_votes = (current_votes < 0 ? 0 : current_votes);  // if current votes <0 then votes = 0
    char *new_votes_str = intToString(current_votes);
    RETURN_ON_NULL(new_votes_str, AREA_OUT_OF_MEMORY);
    if (mapPut(area->votes, tribe_id, new_votes_str) != MAP_SUCCESS)
    {
        free(new_votes_str);
        return AREA_OUT_OF_MEMORY;
    }
    free(new_votes_str);
    return AREA_SUCCESS;
}
#endif // AREA_C
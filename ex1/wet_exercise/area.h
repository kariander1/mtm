
#ifndef AREA_H_
#define AREA_H_

#include <stdbool.h>

typedef struct area_t* Area;
typedef enum AreaResult_t {
    AREA_OUT_OF_MEMORY=1,
    AREA_NULL_ARGUEMENT,
    AREA_SUCCESS
} AreaResult;

/**
* areaCreate: creates a new area 
* initial all area attributes
*
* @param area_id - The area_id of the new area
* @param area_name - The area name of the new area.
* @return
* 	NULL - if allocation failed.
* 	else returns the pointer to the new area 
*/
Area areaCreate(int area_id,const char* area_name);
/**
* areaDestroy: deletes a given area 
*
* @param area - The area to destroy
* @return
* 	void function - does not return anything 
*/
void areaDestroy(Area area);
/**
* areaRemoveTribe: removes all votes from the area to the given tribe (when we want to remove a tribe)
*
* @param area - The area to remove votes from
* @param tribe_id - The tribe to delete his votes .
* @return
* 	void function - does not return anything
*/
void areaRemoveTribe(Area area, const char* tribe_id);
/**
* areaEquals: compare between the id and the given area to check if they are the same - have the same id 
*
* @param area - The area to compare to
* @param id - The id to compare to
* @return
* 	True - if the areaID and the ID are the same.
* 	else returns false
*/
bool areaEquals(Area area,int id);
/**
* areaGetId: get the ID of the given area 
*
* @param area - The area to get it's ID
* @return
* 	the ID of the area 
*/
int areaGetId(Area area);
/**
* areaGetMostVotesTribe: returns the tribe with most votes in the current area
*
* @param area - The area to search for the most voted tribe 
* @return
* 	NULL - if the area is NULL, lse return in a string the ID of the max-votes-tribe 
*/
char *areaGetMostVotesTribe(Area area);
/**
* areaChangeVotesToTribe: change the number of votes from the area to the given tribe
*
* @param area - The area to change it's votes for the tribe
* @param tribe_id - The tribe to change it's votes
* @param area - the number of votes to add or remove (if remove then votes will be negative)
* @return
* 	AREA_NULL_ARGUEMENT - if one of the arguments are NULL
*   AREA_OUT_OF_MEMORY - if memory allocation failed
*   AREA_SUCCESS - if change votes succeeded
*/
AreaResult areaChangeVotesToTribe(Area area, const char* tribe_id, int num_of_votes);

#endif //AREA_H
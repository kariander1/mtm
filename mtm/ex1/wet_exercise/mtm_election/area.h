
#ifndef AREA_H_
#define AREA_H_

#include <stdbool.h>

typedef struct area_t* Area;
typedef enum AreaResult_t {
    AREA_OUT_OF_MEMORY,
    AREA_NULL_ARGUEMENT,
    AREA_SUCCESS,
    AREA_FAILED_CONVERSION,
} AreaResult;

AreaResult areaChangeVotesToTribe(Area area, const char* tribe_id, int num_of_votes);
Area areaCreate(int area_id,const char* area_name);
void areaDestroy(Area area);
AreaResult areaClear(Area area);
bool areaEquals(Area area_1,int id);


#endif //AREA_H
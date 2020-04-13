#ifndef AREA_C
#define AREA_C

#include "area.h"
#include "../mtm_map/map.h"

struct area_t
{
    int area_id;
    char* area_name;
    Map votes;
    
};


Area areaCreate(int area_id,char* area_name)
{
    return NULL;
}
AreaResult areaDestroy(Area area)
{
    return AREA_OUT_OF_MEMORY;
}
AreaResult areaClear(Area area)
{
    return AREA_OUT_OF_MEMORY;
}
bool areaEquals(Area area_1,int id)
{
    return area_1->area_id == id;
}
#endif // AREA_C
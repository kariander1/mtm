
#ifndef AREA_H
#define AREA_H

#include <stdbool.h>

typedef struct area_t* Area;
typedef enum AreaResult_t {
    AREA_OUT_OF_MEMORY,
} AreaResult;

Area areaCreate(int area_id,const char* area_name);
AreaResult areaDestroy(Area area);
AreaResult areaClear(Area area);
bool areaEquals(Area area_1,int id);


#endif //AREA_H
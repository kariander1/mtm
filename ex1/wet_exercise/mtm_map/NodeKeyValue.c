#ifndef NODEKEYVALUE_C_
#define NODEKEYVALUE_C_

#include "NodeKeyValue.h"
#include <stdlib.h>
#include "../macro.h"
#include <string.h>

typedef struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
};




#endif
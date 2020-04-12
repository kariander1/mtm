#include "../mtm_map/map.h"
#include "../map.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OPTIONS 15
#define MAX_MAPS 1000

typedef enum Operation_t
{
    MAP_CREATE = 1,
    MAP_DESTROY,
    MAP_COPY,
    MAP_GET_SIZE,
    MAP_CONTAINS,
    MAP_PUT,
    MAP_GET,
    MAP_REMOVE,
    MAP_GET_FIRST,
    MAP_GET_NEXT,
    MAP_CLEAR,
    MAP_PRINT_INTERNAL,
    MAP_PRINT,
    MAP_ITERATE,
    QUIT
} OperationType;

Map maps[MAX_MAPS];

void operationCreateMap();
void printOptions();
int getSelection();
void operationCreateMap();
bool executeOperations();
int addMapToMaps(Map map);
int operationPrintMapsInternal();
int operationPrintMaps();
void operationClearMap();
void operationCopy();
void operationPut();
void operationDestroyMap();
void operationGetSize();
void removeFromMaps(int index);
void operationGetFirst();

void printOptions()
{
    printf("Please select option: [1-%d]\n", OPTIONS);
    char *option_text;
    for (int i = 1; i <= OPTIONS; i++)
    {
        switch (i)
        {
        case MAP_CREATE:
            option_text = "Create Map";
            break;
        case MAP_DESTROY:
            option_text = "Destroy Map";
            break;
        case MAP_COPY:
            option_text = "Copy Map";
            break;
        case MAP_GET_SIZE:
            option_text = "Get Map Size";
            break;

        case MAP_CONTAINS:
            option_text = "Check Existence of key";
            break;
        case MAP_PUT:
            option_text = "Put Element";
            break;
        case MAP_GET:
            option_text = "Get Element";
            break;
        case MAP_REMOVE:
            option_text = "Remove Element";
            break;
        case MAP_GET_FIRST:
            option_text = "Get first element";
            break;

        case MAP_GET_NEXT:
            option_text = "Get next element";
            break;
        case MAP_CLEAR:
            option_text = "Clear Map";
            break;
        case MAP_PRINT_INTERNAL:
            option_text = "Print Map (internal)";
            break;
        case MAP_PRINT:
            option_text = "Print Map (script)";
            break;
        case MAP_ITERATE:
            option_text = "Iterate Map";
            break;
        case QUIT:
            option_text = "Quit";
            break;
        default:
            break;
        }
        printf("%d - %s\n", i, option_text);
    }
}
int getSelection(int lower, int upper, int exception)
{
    int option = -1;
    while (!scanf("%d", &option) || ((option < lower || option > upper) && option != exception))
    {
        printf("Invalid input\n");
    }
    return option;
}
bool executeOperations()
{
    int selection = getSelection(1, OPTIONS, 1);
    switch (selection)
    {
    case MAP_CREATE:
        operationCreateMap();
        break;
    case MAP_DESTROY:
        operationDestroyMap();
        break;
    case MAP_CLEAR:
        operationClearMap();
        break;
    case MAP_PRINT_INTERNAL:
        operationPrintMapsInternal();
        break;
    case MAP_PRINT:
        operationPrintMaps();
        break;
    case MAP_GET_SIZE:
        operationGetSize();
        break;
    case MAP_PUT:
        operationPut();
        break;
    case MAP_COPY:
        operationCopy();
        break;
    case MAP_CONTAINS:
        operationContains();
        break;
    case MAP_GET:
        operationGet();
        break;
    case MAP_REMOVE:
        operationRemove();
        break;
    case MAP_ITERATE:
        operationIterate();
        break;
    case MAP_GET_FIRST:
        operationGetFirst();
        break;
    case MAP_GET_NEXT:
        operationGetNext();
        break;
    default:
    case QUIT:
        return true;
    }
    return false;
}
void operationGetNext()
{/*
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    */
    printf("From which map would you like to GetNext? [0-%d]\n", MAX_MAPS);
    int selection = getSelection(0, MAX_MAPS, 0);
    char *next = mapGetNext(maps[selection]);
    printf("Next entry is : %s\n", next);
}
void operationGetFirst()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to GetFirst? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    char *first = mapGetFirst(maps[selection]);
    printf("First entry is : %s\n", first);
}
void operationIterate()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to iterate? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);

    char *it_string;
    MAP_FOREACH(it_string, maps[selection])
    {
        printf("%s\n", it_string);
    }
}
void operationRemove()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to remove? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    char key[50];
    printf("Which key would you like to remove?\n");
    scanf("%s", key);
    MapResult status = mapRemove(maps[selection], key);
    char *status_string = "UNDEFINED";
    switch (status)
    {
    case MAP_SUCCESS:
        status_string = "MAP_SUCCESS";
        break;
    case MAP_NULL_ARGUMENT:
        status_string = "MAP_NULL_ARGUMENT";
        break;
    case MAP_ITEM_DOES_NOT_EXIST:
        status_string = "MAP_ITEM_DOES_NOT_EXIST";
        break;
    case MAP_ERROR:
        status_string = "MAP_ERROR";
        break;
    default:
        break;
    }
    printf("Key %s removed has status of %s\n", key, status_string);
}
void operationGet()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to get? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);

    char key[50];
    printf("Which key would you like to get?\n");
    scanf("%s", key);
    char *value = mapGet(maps[selection], key);
    printf("Key %s has value of %s\n", key, value);
}
void operationContains()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to search? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    char key[50];
    printf("Which key would you like to search?\n");
    scanf("%s", key);
    bool contains = mapContains(maps[selection], key);
    char *found_status = contains ? "Found" : "Not Found";
    printf("Key %s was %s\n", key, found_status);
}
void operationCopy()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("Which map would you like to copy? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    Map new_map = mapCopy(maps[selection]);
    int new_i = addMapToMaps(new_map);

    printf("Map N.%d Copied to new Map N.%d\n", selection, new_i);
}
void operationPut()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }

    printf("Which map would you like to put in? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    printf("How many keys & values would you like to insert?\n");
    int num_of_vals = 0;
    if (!scanf("%d", &num_of_vals))
    {
        printf("Invalid input\n");
        return;
    }
    for (int i = 0; i < num_of_vals; i++)
    {
        char key[50], value[50];
        printf("Please enter key:\n");
        scanf("%s", key);
        printf("Please enter value:\n");
        scanf("%s", value);
        mapPut(maps[selection], key, value);
    }
}
int getMaxIndexOfMapsWithPrint()
{
    int maxi = operationPrintMaps();
    if (maxi == -1)
    {
        printf("No maps stored\n");
    }
    return maxi;
}
void operationGetSize()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }

    printf("Which map would you like to get size from? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    int size = mapGetSize(maps[selection]);
    printf("Map N.%d Size is : %d\n", selection, size);
}
void operationCreateMap()
{
    Map new_map = mapCreate();
    addMapToMaps(new_map);
}
void operationDestroyMap()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("Which map would you like to destroy? [0-%d] [-9->Destroy all]\n", maxi);
    int selection = getSelection(0, maxi, -9);
    if (selection == -9)
    {
        for (int i = 0; i < MAX_MAPS; i++)
        {
            if (maps[i])
            {
                mapDestroy(maps[i]);
                removeFromMaps(i);
            }
        }
    }
    else
    {
        mapDestroy(maps[selection]);
        removeFromMaps(selection);
    }
}
void operationClearMap()
{
    int maxi = getMaxIndexOfMapsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("Which map would you like to clear? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    mapClear(maps[selection]);
}
int operationPrintMaps()
{
    int count = 0;
    int max_map_index = -1;
    for (int i = 0; i < MAX_MAPS; i++)
    {

        if (maps[i])
        {
            printf("Map N. %d\n\n", i);
            max_map_index = i;
            char *current_key;
            int num_elements = mapGetSize(maps[i]);
            int k = 0;
            int spaces_for_key = 20;
            int spaces_for_value = 20;

            MAP_FOREACH(current_key, maps[i])
            {
                if (k == 0)
                {
                    putchar(' ');
                    printf("key");
                    for (int i = 0; i <= spaces_for_key - 3; i++)
                    {
                        putchar(' ');
                    }
                    printf("value\n");

                    putchar(' ');
                    for (int i = 0; i < spaces_for_key; i++)
                    {
                        putchar('-');
                    }
                    putchar(' ');
                    for (int i = 0; i < spaces_for_value; i++)
                    {
                        putchar('-');
                    }
                    putchar(' ');
                    putchar('\n');
                }

                printf("|%-20s|", current_key);

                printf("%-20s|\n", mapGet(maps[i], current_key));

                k++;
                if (k == num_elements)
                { // Print ending
                    putchar(' ');
                    for (int i = 0; i < spaces_for_key; i++)
                    {
                        putchar('-');
                    }
                    putchar(' ');
                    for (int i = 0; i < spaces_for_value; i++)
                    {
                        putchar('-');
                    }
                    putchar(' ');
                    putchar('\n');
                }
            }

            count++;
            printf("\n");
        }
    }
    return max_map_index;
}
int operationPrintMapsInternal()
{
    int count = 0;
    int max_map_index = -1;
    for (int i = 0; i < MAX_MAPS; i++)
    {

        if (maps[i])
        {
            printf("Map N. %d\n\n", i);
            max_map_index = i;
            mapPrint(maps[i]);
            count++;
            printf("\n");
        }
    }
    return max_map_index;
}

int addMapToMaps(Map map)
{
    for (int i = 0; i < MAX_MAPS; i++)
    {
        if (!maps[i])
        {
            maps[i] = map;
            return i;
        }
    }
    return -1;
}
void removeFromMaps(int index)
{
    maps[index] = NULL;
}

int main()
{
    for (int i = 0; i < MAX_MAPS; i++)
    {
        maps[i] = NULL;
    }

    printf("Welcome to map tester V1.5 C Shai Yehezkel\n\n");
    do
    {
        printOptions();
    } while (!executeOperations());
    return 0;
}

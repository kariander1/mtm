#include "../mtm_map/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OPTIONS 16
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
    MAP_INPUTS,
    QUIT
} OperationType;

typedef struct node_tt
{
    char *key;
    char *value;
    struct node_tt *next;
} * node;

Map maps[MAX_MAPS];
int inputs = 0;

static bool supress_printer = false;

void printMapResult(MapResult result);
void operationsOverrideInputs();
void operationCreateMap();
void printOptions();
int getSelection();
void operationCreateMap();
bool executeOperations();
int addMapToMaps(Map map);
int operationPrintMapsInternal();
int operationPrintMaps(bool lexi);
int operationPrintMapSelector();
void printLexicoggraphic(Map map);
void operationClearMap();
void operationCopy();
void operationPut();
void operationDestroyMap();
void operationGetSize();
void removeFromMaps(int index);
void operationGetFirst();
void operationContains();
void operationGet();
void operationRemove();
void operationIterate();
void operationGetNext();
int getMaxIndexOfMapsWithPrint();
char *getOptionText(int i);

char *getOptionText(int i)
{
    char *option_text = "";
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
    case MAP_INPUTS:
        option_text = "Override Inputs";
        break;
    case QUIT:
        option_text = "Quit";
        break;
    default:
        break;
    }

    return option_text;
}
void printOptions()
{
    printf("Please select option: [1-%d]\n", OPTIONS);
    char *option_text;
    for (int i = 1; i <= OPTIONS; i++)
    {
        option_text = getOptionText(i);
        printf("%d - %s\n", i, option_text);
    }
}
int getSelection(int lower, int upper, int exception)
{
    int option = -1;
    while (!scanf("%d", &option))
    {
        inputs++;
        printf("Invalid input - input N.%d\n", inputs);
        exit(0);
    }
    printf("Got selection : %d\n", option);
    inputs++;
    return option;
}
bool executeOperations()
{
    int selection = OPTIONS; //Quit;
    selection = getSelection(1, OPTIONS, 1);

    char* option_text =getOptionText(selection);
    printf("Chosen operation : %s\n\n", option_text);
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
        operationPrintMaps(true);
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
    case MAP_INPUTS:
        operationsOverrideInputs();
        break;
    default:
    case QUIT:
        return true;
    }
    return false;
}
void operationsOverrideInputs()
{
    printf("mapDestroy(NULL):");
    mapDestroy(NULL);
    putchar('\n');
    printf("mapCopy(NULL)");
    mapCopy(NULL);
    putchar('\n');
    printf("mapGetSize(NULL)");
    mapGetSize(NULL);
    putchar('\n');
    printf("mapContains(NULL,NULL)");
    mapContains(NULL, NULL);
    putchar('\n');
    printf("mapContains(NULL,)");
    mapContains(NULL, "");
    putchar('\n');

    Map tempMap = mapCreate();

    printf("mapContains(map,NULL)");
    mapContains(tempMap, NULL);
    putchar('\n');
    printf("mapContains(map,)");
    mapContains(tempMap, "");
    putchar('\n');

    printf("mapPut(NULL,NULL,NULL)");
    printMapResult(mapPut(NULL, NULL, NULL));
    putchar('\n');

    printf("mapPut(NULL,,NULL);");
    printMapResult(mapPut(NULL, "", NULL));
    putchar('\n');

    printf("mapPut(NULL,NULL,);");
    printMapResult(mapPut(NULL, NULL, ""));
    putchar('\n');

    printf("mapPut(NULL,,);");
    printMapResult(mapPut(NULL, "", ""));
    putchar('\n');

    printf("mapPut(map,NULL,NULL);");
    printMapResult(mapPut(tempMap, NULL, NULL));
    putchar('\n');

    printf("mapPut(map,NULL,"
           ");");
    printMapResult(mapPut(tempMap, NULL, ""));
    putchar('\n');

    printf("mapPut(map,"
           ",NULL)");
    printMapResult(mapPut(tempMap, "", NULL));
    putchar('\n');

    printf("mapPut(map,,);");
    printMapResult(mapPut(tempMap, "", ""));
    putchar('\n');

    printf("mapGet(NULL,NULL)");
    printf("%s", mapGet(NULL, NULL));
    putchar('\n');
    printf("mapGet(NULL,)");
    printf("%s", mapGet(NULL, ""));
    putchar('\n');

    printf("mapGet(map,NULL)");
    printf("%s", mapGet(tempMap, NULL));
    putchar('\n');
    printf("mapGet(map,)");
    printf("%s", mapGet(tempMap, ""));
    putchar('\n');

    printf("mapGet(NULL,NULL)");
    printMapResult(mapRemove(NULL, NULL));
    putchar('\n');
    printf("mapGet(NULL,)");
    printMapResult(mapRemove(NULL, ""));
    putchar('\n');

    printf("mapGet(map,NULL)");
    printMapResult(mapRemove(tempMap, NULL));
    putchar('\n');
    printf("mapGet(map,)");
    printMapResult(mapRemove(tempMap, ""));
    putchar('\n');

    printf("mapClear(NULL)");
    mapClear(NULL);
    putchar('\n');

    mapDestroy(tempMap);
}
void operationGetNext()
{ /*
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
    printf("Got key : %s\n", key);
    inputs++;
    MapResult status = mapRemove(maps[selection], key);
    printMapResult(status);
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
    printf("Got key : %s\n", key);
    inputs++;
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
    printf("Got key : %s\n", key);
    inputs++;
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
        inputs++;
        printf("Invalid input input N.%d\n", inputs);
        exit(0);
        return;
    }
    printf("Got num_of_vals : %d\n", num_of_vals);
    inputs++;
    for (int i = 0; i < num_of_vals; i++)
    {
        char key[50], value[50];
        printf("Please enter key:\n");
        scanf("%s", key);

        printf("Got key : %s\n", key);
        inputs++;
        printf("Please enter value:\n");
        scanf("%s", value);
        printf("Got value : %s\n", value);
        inputs++;
        printMapResult(mapPut(maps[selection], key, value));
    }
}
int getMaxIndexOfMapsWithPrint()
{
    int maxi = operationPrintMapSelector();
    if (maxi == -1)
    {
        printf("No maps stored\n");
    }
    return maxi;
}
int operationPrintMapSelector()
{
    if (supress_printer)
    {
        return operationPrintMapsInternal();
    }
    return operationPrintMaps(false);
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
    printMapResult(mapClear(maps[selection]));
}
void printMapResult(MapResult result)
{
    char *status_string = "UNDEFINED";
    switch (result)
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
    case MAP_OUT_OF_MEMORY:
        status_string = "MAP_OUT_OF_MEMORY";
        break;
    case MAP_ITEM_ALREADY_EXISTS:
        status_string="MAP_ITEM_ALREADY_EXISTS";
        break;
    default:
        break;
    }
    printf("Operation end with status of %s\n", status_string);
}
void sortEntries(Map map,node* head)
{

    (*head) = NULL;
    MAP_FOREACH(key, map)
    { //=malloc(sizeof(*sorted_list))
        char *value = mapGet(map, key);
        
        node dummy = malloc(sizeof(*dummy));
        node temp =dummy;
        temp->next = (*head);
        int k = 0;
        while (temp->next && strcmp(key, temp->next->key) > 0)
        {
            temp = temp->next;
            k++;
        }
     
        node after = temp->next;
        node new_node = malloc(sizeof(*new_node));
        new_node->key = key;
        new_node->value = value;

        temp->next = new_node;

        if (k == 0)
        {
            *head = temp->next;
        }
        new_node->next = after;
        free(dummy);
    }
    return;
}
void printLexicoggraphic(Map map)
{
    //printf("Map N. %d\n\n", i);
    //        max_map_index = i;
    int num_elements = mapGetSize(map);
    int k = 0;
    int spaces_for_key = 20;
    int spaces_for_value = 20;
node head;
     sortEntries(map,&head);
    node sorted = head;
    while (sorted)
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

        printf("|%-20s|", (sorted->key));

        printf("%-20s|\n", sorted->value);

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
        sorted = sorted->next;
    }

    printf("\n");
    while (head)
    {
        node to_free = head;
        head=head->next;
            free(to_free);
    }
    

    free(sorted);
}

int operationPrintMaps(bool lexi)
{
    //  int count = 0;
    int max_map_index = -1;
    for (int i = 0; i < MAX_MAPS; i++)
    {

        if (maps[i])
        {
            printf("Map N. %d\n\n", i);
            max_map_index = i;

            if (lexi)
            {
                printLexicoggraphic(maps[i]);
            }
            else
            {
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
                printf("\n");
            }

            //     count++;
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
            //mapPrint(maps[i]);
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
    printf("Welcome to map tester V3.3 C Shai Yehezkel\n\n");
    printf("**NOTE : The built-in printer utilizes the MAP_FOREACH Macro, and thus changes the iterator every print.\n\n");
    printf("Would you like to suppress printer? (Y/N)");
    char selection = getchar();
    inputs++;
    if (selection == 'y' || selection == 'Y')
    {
        supress_printer = true;
    }

    do
    {
        printOptions();
    } while (!executeOperations());
    return 0;
}


#include "../election.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OPTIONS 14
#define MAX_ELECTIONS 1000

typedef enum Operation_t
{
    ELECTION_CREATE = 1,
    ELECTION_DESTROY,
    ADD_TRIBE,
    ADD_AREA,
    GET_TRIBE_NAME,
    ADD_VOTE,
    REMOVE_VOTE,
    SET_TRIBE_NAME,
    REMOVE_TRIBE,
    REMOVE_AREAS,
    TRIBES_MAP,
    ELECTION_PRINT,
    ELECTION_INPUTS,
    QUIT
} OperationType;

Election elections[MAX_ELECTIONS];
int inputs=0;

static bool internal_printer = false;

void printMapResult(MapResult result);
void operationsOverrideInputs();
void operationCreateElection();
void printOptions();
int getSelection();

bool executeOperations();

int operationPrintElectionsInternal();
int operationPrintElections();
int operationPrintElectionSelector();
int addElecToElecs(Election elec);
void removeFromElections(int index);

int getMaxIndexOfElectionsWithPrint();
char* getOptionText(int i);

char* getOptionText(int i)
{
        char *option_text;
switch (i)
        {
        case ELECTION_CREATE:
            option_text = "Create Election";
            break;
        case ELECTION_DESTROY:
            option_text = "Destroy Election";
            break;
        case ADD_TRIBE:
            option_text = "Add Tribe";
            break;
        case ADD_AREA:
            option_text = "Add Area";
            break;

        case GET_TRIBE_NAME:
            option_text = "Get Tribe Name";
            break;
        case ADD_VOTE:
            option_text = "Add Vote";
            break;
        case REMOVE_VOTE:
            option_text = "Remove Vote";
            break;
        case SET_TRIBE_NAME:
            option_text = "Set Tribe Name";
            break;
        case REMOVE_TRIBE:
            option_text = "Remove Tribe";
            break;

        case REMOVE_AREAS:
            option_text = "Remove Areas";
            break;
        case TRIBES_MAP:
            option_text = "Areas-to-Tribes mapping";
            break;
        case ELECTION_PRINT:
            option_text = "Print Election";
            break;
        case ELECTION_INPUTS:
            option_text = "Inputs override";
            break;
            default:
        case QUIT:
            option_text = "Quit";
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
        printf("Invalid input - input N.%d\n",inputs);
     
    }
    printf("Got selection : %d\n",option);
    inputs++;
    return option;
}
bool executeOperations()
{
    int selection = getSelection(1, OPTIONS, 1);
    printf("Chosen operation : %s\n\n",getOptionText(selection));
    switch (selection)
    {
    case ELECTION_CREATE:
        operationCreateElection();
        break;
    case ELECTION_DESTROY:
        operationDestroyElection();
        break;
    case MAP_CLEAR:
        operationClearMap();
        break;
        
    case ELECTION_PRINT:
        operationPrintElections();
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
    mapContains(NULL,NULL);
    putchar('\n');
    printf("mapContains(NULL,)");
    mapContains(NULL,"");
    putchar('\n');

    Map tempMap = mapCreate();

    printf("mapContains(map,NULL)");
    mapContains(tempMap,NULL);
    putchar('\n');
        printf("mapContains(map,)");
    mapContains(tempMap,"");
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
    
    printf("mapPut(map,NULL,"");");
    printMapResult(mapPut(tempMap, NULL, ""));
    putchar('\n');


    
    printf("mapPut(map,"",NULL)");
    printMapResult(mapPut(tempMap, "", NULL));
    putchar('\n');

            printf("mapPut(map,,);");
    printMapResult(mapPut(tempMap, "", ""));
    putchar('\n');



    printf("mapGet(NULL,NULL)");
    printf("%s",mapGet(NULL,NULL));
    putchar('\n');
    printf("mapGet(NULL,)");
     printf("%s",mapGet(NULL,""));
    putchar('\n');


    printf("mapGet(map,NULL)");
     printf("%s",mapGet(tempMap,NULL));
    putchar('\n');
        printf("mapGet(map,)");
     printf("%s",mapGet(tempMap,""));
    putchar('\n');


    printf("mapGet(NULL,NULL)");
    printMapResult(mapRemove(NULL,NULL));
    putchar('\n');
    printf("mapGet(NULL,)");
     printMapResult(mapRemove(NULL,""));
    putchar('\n');


    printf("mapGet(map,NULL)");
     printMapResult(mapRemove(tempMap,NULL));
    putchar('\n');
        printf("mapGet(map,)");
     printMapResult(mapRemove(tempMap,""));
    putchar('\n');


        printf("mapClear(NULL)");
     mapClear(NULL);
    putchar('\n');

    mapDestroy(tempMap);



}
void operationGetNext()
{ 

    printf("From which map would you like to GetNext? [0-%d]\n", MAX_ELECTIONS);
    int selection = getSelection(0, MAX_ELECTIONS, 0);
    
    char *next = mapGetNext(maps[selection]);
    printf("Next entry is : %s\n", next);
}
void operationGetFirst()
{
    int maxi = getMaxIndexOfElectionsWithPrint();
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
    int maxi = getMaxIndexOfElectionsWithPrint();
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
    int maxi = getMaxIndexOfElectionsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to remove? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    char key[50];
    printf("Which key would you like to remove?\n");
    scanf("%s", key);
    printf("Got key : %s\n",key);
    inputs++;
    MapResult status = mapRemove(maps[selection], key);
    printMapResult(status);
}
void operationGet()
{
    int maxi = getMaxIndexOfElectionsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to get? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);

    char key[50];
    printf("Which key would you like to get?\n");
    scanf("%s", key);
     printf("Got key : %s\n",key);
    inputs++;
    char *value = mapGet(maps[selection], key);
    printf("Key %s has value of %s\n", key, value);
}
void operationContains()
{
    int maxi = getMaxIndexOfElectionsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("From which map would you like to search? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    char key[50];
    printf("Which key would you like to search?\n");
    scanf("%s", key);
     printf("Got key : %s\n",key);
    inputs++;
    bool contains = mapContains(maps[selection], key);
    char *found_status = contains ? "Found" : "Not Found";
    printf("Key %s was %s\n", key, found_status);
}
void operationCopy()
{
    int maxi = getMaxIndexOfElectionsWithPrint();
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
    int maxi = getMaxIndexOfElectionsWithPrint();
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
        printf("Invalid input input N.%d\n",inputs);
        exit(0);
        return;
    }
     printf("Got num_of_vals : %d\n",num_of_vals);
    inputs++;
    for (int i = 0; i < num_of_vals; i++)
    {
        char key[50], value[50];
        printf("Please enter key:\n");
        scanf("%s", key);

           printf("Got key : %s\n",key);
        inputs++;
        printf("Please enter value:\n");
        scanf("%s", value);
            printf("Got value : %s\n",value);
        inputs++;
        printMapResult(mapPut(maps[selection], key, value));
    }
}
int getMaxIndexOfElectionsWithPrint()
{
    int maxi = operationPrintElectionSelector();
    if (maxi == -1)
    {
        printf("No elections stored\n");
    }
    return maxi;
}
int operationPrintElectionSelector()
{
    if (internal_printer)
    {
        return operationPrintElectionsInternal();
    }
    return operationPrintElections();
}
void operationGetSize()
{
    int maxi = getMaxIndexOfElectionsWithPrint();
    if (maxi == -1)
    {
        return;
    }

    printf("Which map would you like to get size from? [0-%d]\n", maxi);
    int selection = getSelection(0, maxi, 0);
    int size = mapGetSize(maps[selection]);
    printf("Map N.%d Size is : %d\n", selection, size);
}
void operationCreateElection()
{
    Election new_elec = electionCreate();
    addElecToElecs(new_elec);
}
void operationDestroyElection()
{
    int maxi = getMaxIndexOfElectionsWithPrint();
    if (maxi == -1)
    {
        return;
    }
    printf("Which election would you like to destroy? [0-%d] [-9->Destroy all]\n", maxi);
    int selection = getSelection(0, maxi, -9);
    if (selection == -9)
    {
        for (int i = 0; i < MAX_ELECTIONS; i++)
        {
            if (elections[i])
            {
                electionDestroy(elections[i]);
                removeFromElections(i);
            }
        }
    }
    else
    {
        electionDestroy(elections[selection]);
        removeFromElections(selection);
    }
}
void operationClearMap()
{
    int maxi = getMaxIndexOfElectionsWithPrint();
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
int operationPrintElections()
{
    int count = 0;
    int max_map_index = -1;
    for (int i = 0; i < MAX_ELECTIONS; i++)
    {

        if (elections[i])
        {
            printf("Map N. %d\n\n", i);
            max_map_index = i;
            int num_elements = mapGetSize(elections[i]);
            int k = 0;
            int spaces_for_key = 20;
            int spaces_for_value = 20;

            MAP_FOREACH(current_key, elections[i])
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

                printf("%-20s|\n", mapGet(elections[i], current_key));

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
int operationPrintElectionsInternal()
{
    int count = 0;
    int max_election_index = -1;
    for (int i = 0; i < MAX_ELECTIONS; i++)
    {

        if (elections[i])
        {
            printf("Map N. %d\n\n", i);
            max_election_index = i;
            //mapPrint(maps[i]);
            count++;
            printf("\n");
        }
    }
    return max_election_index;
}

int addElecToElecs(Election elec)
{
    for (int i = 0; i < MAX_ELECTIONS; i++)
    {
        if (!elections[i])
        {
            elections[i] = elec;
            return i;
        }
    }
    return -1;
}
void removeFromElections(int index)
{
    elections[index] = NULL;
}


int main()
{
    for (int i = 0; i < MAX_ELECTIONS; i++)
    {
        elections[i] = NULL;
    }
    printf("Welcome to map tester V1.6 C Shai Yehezkel\n\n");
    printf("Using internal printer calls the \"void mapPrint\" implemented in map.h/c.\nOtherwise a built-in printer is being called that would be the same for each implementation.\n\n");
    printf("**NOTE : The built-in printer utilizes the MAP_FOREACH Macro, and thus changes the iterator every print.\n\n");
    printf("Would you like to use internal printer for prints? (Y/N) ");
    char selection = getchar();
    inputs++;
    if (selection == 'y' || selection == 'Y')
    {
        internal_printer = true;
    }

    do
    {
        printOptions();
    } while (!executeOperations());
    return 0;
}

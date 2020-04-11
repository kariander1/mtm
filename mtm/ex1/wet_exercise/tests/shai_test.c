#include "../mtm_map/map.h"
#include "../map.c"
#include <stdlib.h>
#include <stdio.h>

#define OPTIONS 11
#define MAX_MAPS 1000

Map maps[MAX_MAPS];


void operationCreateMap();
void printOptions();
int getSelection();
void operationCreateMap();
bool executeOperations();
void addMapToMaps(Map map);

void printOptions()
{
    printf("Please select option: [1-12]");
    char *option_text;
    for (int i = 0; i < OPTIONS; i++)
    {
        switch (i)
        {
        case 0:
            option_text = "Create Map";
            break;
        case 1:
            option_text = "Destroy Map";
            break;
        case 2:
            option_text = "Copy Map";
            break;
        case 3:
            option_text = "Get Map Size";
            break;

        case 4:
            option_text = "Check Existence of key";
            break;
        case 5:
            option_text = "Put Element";
            break;
        case 6:
            option_text = "Get Element";
            break;
        case 7:
            option_text = "Remove Element";
            break;
        case 8:
            option_text = "Get first element";
            break;

        case 9:
            option_text = "Get next element";
            break;
        case 10:
            option_text = "Print Map";
            break;
            case 11:
            option_text = "Quit";
            break;
        default:
            break;
        }
        printf("%d - %s\n", i + 1, option_text);
    }
}
int getSelection()
{
    int option=-1;
    while(!scanf("%d",&option) || option<1 || option>11)
    {
        printf("Invalid input");
    }
    return option;
}
bool executeOperations()
{
    int selection = getSelection();
    switch (selection)
    {
    case 1:
        operationCreateMap();
        break;
    case 11:
        return true;
    default:
        break;
    }
    return false;
}
void operationCreateMap()
{
    Map new_map = mapCreate();
    addMapToMaps(new_map);
}


void addMapToMaps(Map map)
{
    for (int i = 0; i < MAX_MAPS; i++)
    {
        if(!maps[i])
        {
            maps[i] =map;
        }
    }
    
}



int main()
{
  for (int i = 0; i < MAX_MAPS; i++)
  {
      maps[i]=NULL;
  }
  
    printf("Welcome to map tester V1.0 C Shai Yehezkel");
    do
    {
        printOptions();
    } while (!executeOperations());
    return 0;
}
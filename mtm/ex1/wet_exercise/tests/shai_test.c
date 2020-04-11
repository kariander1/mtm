#include "../mtm_map/map.h"
#include <stdlib.h>
#include <stdio.h>

#define OPTIONS 7
#define MAX_MAPS 1000

void printOptions()
{
    printf("Please select option: [1-11]");
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
        default:
            break;
        }
        printf("%d - %s\n", i + 1, option_text);
    }
}
int getSelection()
{
    int option=-1;
    while(!scanf("%d",option) || option<1 || option>11)
    {
        printf("Invalid input");
    }
    return option;
}
void executeOperations()
{
    int selection = getSelection();
    switch (selection)
    {
    case 1:
        operationCreateMap();
        break;
    
    default:
        break;
    }
}
void operationCreateMap()
{

}

Map[MAX_MAPS] maps;
int main()
{
    printf("Welcome to map tester V1.0 C Shai Yehezkel");
    print_options();


    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static int findLengthOfInt(int num)
{
    int length = 1;
    while(num>10){
        length++;
        num = num/10;
    }
    return length;
}
static int transformStringToInt(char* str)
{
    int num = 0;
    for(int i=0; str[i]!= '\0'; i++){
        num = num*10 + str[i] - '0';
    }
    return num;
}
int main()
{
    int len = findLengthOfInt(105);
    int temp = transformStringToInt("105");
    return 0;
}
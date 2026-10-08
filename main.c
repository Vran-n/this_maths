#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utilities/printcmd.h"

const char *QUIT_CMD = ":q";

bool isNumeric(char ch);
bool isString_Numeric(char *ch);
void scanInt(char *ch);



int main() {
    char *result = calloc(sizeof(char), 64);
    //puts("Hello World!");
    //printf("Enter \"%s\" to quit\n", QUIT_CMD);
    //scanInt(result);
    free(result);

    PrintF("%s\n", "yoyo");
    PrintF("%d is a %s number!\n", 1000, "BIG");
    PrintF("%i is a %c%c%c number!\n", 1000000, 'B', 'I', 'G');
    PrintF("This is %%%d epic\n", 100);
    return 0; 
}

// Returns true if the character is a number
bool isNumeric(char ch) { return (ch <= 57 && ch >= 48); } 

// Returns true if the string is a signed or unsigned int
bool isString_Numeric(char *ch) 
{
    bool isNumber = true;
    size_t len = strlen(ch);
    if (len == 1 && ch[0] == 45) { return false; }
    
    isNumber = isNumeric(ch[0]) || ch[0] == 45 ? true : false;

    for (int i = 1; i < len; i++) 
    {
        bool result = isNumeric(ch[i]);
        if (result == false) { isNumber = false; }
    }

    return isNumber;
}

// where the input is
void scanInt(char *ch) 
{
    printf("Enter Number:\t");
    scanf("%s", ch);
    if (strcmp(ch, QUIT_CMD) == 0) 
    {
        puts("\nSUCCESSFULLY QUIT THE PROGRAM");
        free(ch);
        exit(0);
    }

    bool isNum = isString_Numeric(ch);
    if (isNum == false) 
    { 
        printf("%s is not a number!\n", ch);
        scanInt(ch); 
    }
    return;
}

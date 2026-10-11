#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utilities/printcmd.h"
#include "utilities/strexten.h"
#include "utilities/strstuff.h"

const char *QUIT_CMD = ":q";

bool isNumeric(char ch);
bool isString_Numeric(char *ch);
void scanInt(char *ch);



int main() {
    char *result = calloc(sizeof(char), 64);
    PrintFNL("Hello World!");
    PrintFNL("Enter \"%s\" on any field to quit", QUIT_CMD);
    scanInt(result);
    free(result);
    
    PrintFNL("Hello");
    PrintFNL("This is a test on my printing method.");
    PrintFNL("If this works as it should");
    PrintFNL("There must be 4 strings stored in the list.");
    PrintFNL("%s\n%c\n%%\n%i\n%d", "Hello", 'h', 4, 7);
    //printf("\033[1A\r\033[2K");
    //printf("\033[1A\r\033[2K");
    //printf("\033[1A\r\033[2K");
    return 0; 
}

// Returns true if the character is a number
bool isNumeric(char ch) { return (ch <= 57 && ch >= 48); } 

// Returns true if the string is a signed or unsigned int
bool isString_Numeric(char *ch) 
{
    bool isNumber = true;
    size_t len = strlen(ch);
    if (len == 1 && ch[0] == 45) return false;
    
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
    PrintFN("Enter Number:\t");
    scanf("%s", ch);
    if (strcmp(ch, QUIT_CMD) == 0) 
    {
        PrintFNL("\nSUCCESSFULLY QUIT THE PROGRAM");
        free(ch);
        exit(0);
    }

    bool isNum = isString_Numeric(ch);
    if (isNum == false) 
    { 
        PrintFNL("%s is not a number!", ch);
        scanInt(ch); 
    }
    return;
}

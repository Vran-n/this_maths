#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../utilities/printcmd.h"
#include "extra.h"



void scanQuitCommand(char *ch)
{
    if (strcmp(ch, QUIT_COMMAND) == 0) 
    {
        PrintFN("\nYOU QUIT THE PROGRAM\n");
        free(ch);
        exit(0);
    }
}

bool isNumeric(char ch) { return (ch <= 57 && ch >= 48); } 

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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "utilities/printcmd.h"
#include "methods/equations.h"
#include "miscellaneous/extra.h"

bool ask_user_equation(void);
int8_t reask_user_equation(void);
void scanInt(char *ch, bool first);



int main() {
    srand(time(NULL));
    //char *result = calloc(sizeof(char), 64);
    //PrintFN("Hello World!\n");
    //PrintFN("Enter \"%s\" on any field to quit\n", QUIT_CMD);
    //scanInt(result, true);
    //free(result);
    //PrintFN("1).\t3 x 4 = ?\n");
    user_ask_pick_digits();
    bool result = ask_user_equation();
    return 0; 
}

bool ask_user_equation(void)
{
    char *user_input = malloc(sizeof(char) * 64);
    ans_user answer = new_equation('+');

    PrintFN("Your Answer:\t");
    scanf("%s", user_input);

    int8_t result = answer(user_input);
    
    free(user_input);
    if (result == -1) { return reask_user_equation(); }
    return result == 1 ? true : false;
}

int8_t reask_user_equation(void)
{   
    char *user_input = malloc(sizeof(char) * 64);
    
    ans_user answer = redo_equation();

    PrintFN("Your Answer:\t");
    scanf("%s", user_input);

    RPrintF("");    // clear previous warnings

    int8_t result = answer(user_input);

    free(user_input);
    if (result == -1) { return reask_user_equation(); }
    return result;
}

// where the input is
void scanInt(char *ch, bool first) 
{
    PrintFN("Enter Number:\t");
    scanf("%s", ch);
    scanQuitCommand(ch);

    bool isNum = isString_Numeric(ch);
    if (isNum == false) 
    {   
        if (first == false) 
        {
            RPrintF("");
        }
        RPrintF("%s is not a number!\n", ch);
        scanInt(ch, false); 
    }
    return;
}

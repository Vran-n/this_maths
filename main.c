#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#include "utilities/printcmd.h"
#include "methods/equations.h"
#include "miscellaneous/extra.h"


void ask_user_new_set_questions(uintmax_t question_amount);
void clear_questionaire(unsigned amount);
uintmax_t ask_user_multiple_equations(void);
bool ask_user_equation(void);
int8_t reask_user_equation(void);
void scanInt(char *ch, bool first);



int main() {
    srand(time(NULL));
    //char *result = calloc(sizeof(char), 64);
    //PrintFN("Hello World!\n");
    PrintFN("Enter \"%s\" on any field to quit\n", QUIT_COMMAND);
    //scanInt(result, true);
    //free(result);
    //PrintFN("1).\t3 x 4 = ?\n");

    user_ask_pick_arithmetic();
    user_ask_pick_digits();
    uintmax_t i = ask_user_multiple_equations();
    ask_user_new_set_questions(i);
    return 0; 
}


// do tail call optimazation for this bruv
void ask_user_new_set_questions(uintmax_t question_amount)
{   
    char *user_input = malloc(sizeof(char) * 64);

    PrintFN("Do you want another set of questions? (Y/n)\t");
    scanf("%s", user_input);
    scanQuitCommand(user_input);

    char input = user_input[0];
    size_t len = strlen(user_input);
    free(user_input);

    if (len > 2)
    {
        DPrint();
        ask_user_new_set_questions(question_amount);
        return;
    }
    
    if ((
        input == 'Y' || 
        input == 'y' ||
        input == 'N' ||
        input == 'n'
    ) == false)
    {   
        DPrint();
        ask_user_new_set_questions(question_amount);
        return;
    }

    if (
        input == 'Y' || 
        input == 'y'
    )
    {   
        clear_questionaire(question_amount);
        DPrint();
        
        user_ask_pick_arithmetic();
        user_ask_pick_digits();
        uintmax_t i = ask_user_multiple_equations();
        ask_user_new_set_questions(i);
        return;
    }

    PrintFN("\nYOU QUIT THE PROGRAM\n");
}

void clear_questionaire(unsigned amount)
{
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            DPrint();
        }
    }
}

// same thing in with the multiple methods in equations.c
// ignore it for now
uintmax_t __ask_user_multiple_equations()
{
    char *user_input = malloc(sizeof(char) * 64);

    PrintFN("Enter the number of questions:\t");
    scanf("%s", user_input);
    scanQuitCommand(user_input);

    bool isNum = isString_Numeric(user_input);
    if (isNum == false) 
    {   
        DPrint();
        RPrintF("%s is not a number!\n", user_input);
        return __ask_user_multiple_equations();
    }

    uintmax_t i = strtoumax(user_input, NULL, 10);
    free(user_input);
    if (i > 20) { i = 20; }

    DPrint(); DPrint();

    for (int j = 0; j < i; j++) 
    {   
        bool result = ask_user_equation();
    }

    return i;
}

uintmax_t ask_user_multiple_equations(void)
{
    char *user_input = malloc(sizeof(char) * 64);

    PrintFN("Enter the number of questions:\t");
    scanf("%s", user_input);
    scanQuitCommand(user_input);

    bool isNum = isString_Numeric(user_input);
    if (isNum == false) 
    {   
        RPrintF("%s is not a number!\n", user_input);
        return __ask_user_multiple_equations();
    }

    uintmax_t i = strtoumax(user_input, NULL, 10);
    free(user_input);
    if (i > 20) { i = 20; }

    DPrint();

    for (int j = 0; j < i; j++) 
    {   
        bool result = ask_user_equation();
    }
    return i;
}

bool ask_user_equation(void)
{   
    PrintFN("=========================\n");

    char *user_input = malloc(sizeof(char) * 64);
    ans_user answer = new_equation();

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
    
    DPrint();
    ans_user answer = redo_equation();

    PrintFN("Your Answer:\t");
    scanf("%s", user_input);

    //RPrintF("");    // clear previous warnings

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

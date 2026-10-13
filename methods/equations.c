#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../utilities/printcmd.h"
#include "../miscellaneous/extra.h"
#include "equations.h"



const unsigned MAX_DIGIT = 4;
unsigned Questions = 0;
unsigned Digits = 1;
Arithmetic A_Type = 0;
int32_t current_x = 0; int32_t current_y = 0;


Arithmetic symbol_to_enum(char symbol);

void user_ask_pick_digits();
ans_user new_equation(char arthmetic);
ans_user redo_equation(void);

ans_char ask(unsigned digits);
ans_equation arith_ans(Arithmetic answer);
ans_user ask_addition(int32_t x, int32_t y);
int8_t answer(char *number);



Arithmetic symbol_to_enum(char symbol)
{
    switch (symbol) 
    {
        case '+':
            return 0;
        case '-': 
            return 1;
        case 'x':
        case '*':
            return 2;
        default:
        {
            // incorrect simbol
            PrintFN("Incorrect arithmetic symbol!");
            exit(1);
        }
    }
}



void user_ask_pick_digits()
{   
    char *result = calloc(sizeof(char), 64);
    unsigned digits = 1;

    PrintFN("Enter the number of digits:\t");
    scanf("%s", result);
    scanQuitCommand(result);

    bool isNum = isString_Numeric(result);
    if (isNum == false) 
    {   
        RPrintF("%s is not a number!\n", result);
        user_ask_pick_digits();
        return;
    }

    const uintmax_t i = strtoumax(result, NULL, 10);
    digits = i;

    if (digits > MAX_DIGIT)
    {
        Digits = MAX_DIGIT;
        RPrintF("Entered:\t%d\n", digits);
        PrintFN("Set to:\t\t%d (Capped at %d digits)\n", MAX_DIGIT, MAX_DIGIT);
        free(result);
        return;
    }

    Digits = digits;
    free(result);
}

ans_user new_equation(char arthmetic)
{   
    Arithmetic a_enum = symbol_to_enum(arthmetic);
    ans_equation create_equation = ask(Digits)(a_enum);
    if (create_equation == NULL) { return NULL; }

    // bad practice but whatever
    int a = pow(10, Digits);

    int x = rand() % a;
    int y = rand() % a;
    return create_equation(x, y);
}

ans_user redo_equation(void)
{   
return ask(Digits)(A_Type)(current_x, current_y);
}



ans_char ask(unsigned digits)
{   
    if (digits <= MAX_DIGIT)
    {
        return &arith_ans;
    }
    return NULL;
}

ans_equation arith_ans(Arithmetic answer)
{
    switch (answer) 
    {
        case 0:
        {
            A_Type = 0;
            return &ask_addition;
        }
        case 1: 
        {
            A_Type = 1;
            return NULL;
        }
        case 2:
        {
            A_Type = 2;
            return NULL;
        }
        default:
        {
            // incorrect simbol
            return NULL;
        }
    }
}

ans_user ask_addition(int32_t x, int32_t y)
{   
    current_x = x; current_y = y;
    PrintFN("%d).\t%d + %d = ?\n", Questions + 1, x, y);
    Questions++;
    return &answer;
}

int8_t answer(char *number)
{   
    scanQuitCommand(number);

    bool isNum = isString_Numeric(number);
    if (isNum == false) 
    {   
        Questions--;
        RPrintF("");
        RPrintF("%s is not a number!\n", number);
        return -1;
    }

    intmax_t user_answer = strtoimax(number, NULL, 10);

    switch (A_Type) {
        case 0:
        {   
            int8_t result = current_x + current_y == user_answer ? 1 : 0;
            if (result == true){ PrintFN("Correct!\n"); }
            else { PrintFN("Wrong!\n"); }
            return result;
        }
        case 1:
        {
            return -1;
        }
        case 2:
        {
            return -1;
        }
        default:
        {
            return -1;
        }
    }
}
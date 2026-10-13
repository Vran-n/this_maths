#pragma once
#include <stdint.h>

typedef enum {
    Addition,
    Subtraction,
    Multiplication
} Arithmetic;

// in reverse for obvious reasons
typedef int8_t(* ans_user)(char *);
typedef ans_user(* ans_equation)(int32_t, int32_t);
typedef ans_equation(* ans_char)(Arithmetic);


void user_ask_pick_digits();
ans_user new_equation(char arthmetic);
ans_user redo_equation(void);

ans_char ask(unsigned digits);
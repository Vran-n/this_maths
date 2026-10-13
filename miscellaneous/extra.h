#pragma once
#define QUIT_COMMAND ":q"

// Takes your string input and checks whether or not it is a quit command
void scanQuitCommand(char *ch);

// Returns true if the character is a number
bool isNumeric(char ch);

// Returns true if the string is a signed or unsigned int
bool isString_Numeric(char *ch);
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isNumeric(char ch);
bool isString_Numeric(char *ch);
void scanInt(char *ch);


int main() {
    char *result = calloc(sizeof(char), 64);
    printf("Hello World!\n");
    scanInt(result);
    return 0; 
}

// Returns true if the character is a number
bool isNumeric(char ch) { return (ch <= 57 && ch >= 48); } 

// Returns true if the string is a signed or unsigned int
bool isString_Numeric(char *ch) {
    bool isNumber = true;
    size_t len = strlen(ch);
    if (len == 1 && ch[0] == 45) { return false; }
    
    isNumber = isNumeric(ch[0]) || ch[0] == 45 ? true : false;

    for (int i = 1; i < len; i++) {
        bool result = isNumeric(ch[i]);
        if (result == false) { isNumber = false; }
    }

    return isNumber;
}

void scanInt(char *ch) {
    printf("Enter Number:\t");
    scanf("%s", ch);
    bool isNum = isString_Numeric(ch);
    
    if (isNum == false) { 
        printf("%s is not a number!\n", ch);
        scanInt(ch); 
    }
    return;
}

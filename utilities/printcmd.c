#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "strexten.h"
#include "strstuff.h"

void PrintFNL(const char *restrict format, ...);
void PrintFN(const char *restrict format, ...);



void PrintFNL(const char *restrict format, ...) 
{
    va_list args;
    int count = 0;
    int len = 0;

    char final_str[1000] = "";
    char *format_cpy = strdup(format);
    strcat(format_cpy, "\n");

    char **str_list = str_multi_split(format_cpy, (const char **)FORMATS);
    while (len <= SIZE && str_list[len] != NULL) { len ++; }

    va_start(args, format);

    while (count < len) 
    {   
        char *curr_str = str_list[count];
        PrintFN(curr_str, va_arg(args, void *));
        free(curr_str);
        
        count++;
    }

    va_end(args);
    free(str_list);
}

void PrintFN(const char *restrict format, ...) 
{   
    va_list args;
    int count = 0;
    int len = 0;
    
    char final_str[1000] = "";
    char **str_list = str_multi_split(format, (const char **)FORMATS);
    while (len <= SIZE && str_list[len] != NULL) { len ++; }

    
    //for (int i = 0; i < SIZE && str_list[i] != NULL; i++) {
    //    printf("[%d]\t\"%s\"\n", i, str_list[i]);
    //}
    
    
    va_start(args, format);

    while (count < len - 1) {
        char *curr_str = str_list[count];
        char format[5] = ""; char temp[1000] = "";

        size_t len = strlen(curr_str);

        sprintf(format, "%c%c", curr_str[len-2], curr_str[len-1]);
        
        /////   STRING
        if (strcmp(format, "%s") == 0) 
        {
            char *str = va_arg(args, char *);
            sprintf(temp, "%s%s%s", curr_str, "\b\b\0", str);
        }

        /////   CHARACTER
        if (strcmp(format, "%c") == 0) 
        {
            char ch = va_arg(args, int);
            sprintf(temp, "%s%s%c", curr_str, "\b\b\0", ch);
        }

        /////   INT
        if (strcmp(format, "%d") == 0) 
        {
            int d = va_arg(args, int);
            sprintf(temp, "%s%s%d", curr_str, "\b\b\0", d);
        }

        /////   INT
        if (strcmp(format, "%i") == 0) 
        {
            int d = va_arg(args, int);
            sprintf(temp, "%s%s%d", curr_str, "\b\b\0", d);
        }

        /////   PERCENT
        if (strcmp(format, "%%") == 0) 
        {
            sprintf(temp, "%s%s", curr_str, "\b\0");
        }

        strcat(final_str, temp);
        free(curr_str);
        count++;
    }
    
    
    char *curr_str = str_list[count];
    strcat(final_str, curr_str);
    printf("%s", final_str);

    va_end(args);
    free(str_list);
}
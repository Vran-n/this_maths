#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "strexten.h"
#include "strstuff.h"

typedef struct {
    char *Strings[10];
    unsigned Length;
} List;

typedef struct {
    List Lists[10];
    unsigned Length;
} Block;

Block prnt = {
    .Lists = {},
    .Length = 0,
};


void PrintFNL(const char *restrict __format, ...);
void PrintFN(const char *restrict __format, ...);
void PrintCArr(char **array, const int __size);

void PrintFL(
    const char *restrict    __format,
    ...
) 
{
    va_list args;
    int count = 0;
    int len = 0;

    char final_str[1000] = "";
    char *format_cpy = strdup(__format);
    strcat(format_cpy, "\n");

    char **str_list = str_multi_split(format_cpy, FORMATS, FORMAT_AMT);
    while (len <= SIZE && str_list[len] != NULL) { len ++; }

    va_start(args, __format);

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

void PrintFNL(
    const char *restrict    __format, 
    ...
) 
{
    va_list args;
    int count = 0;
    int len = 0;

    char final_str[1000] = "";
    char *format_cpy = strdup(__format);
    strcat(format_cpy, "\n");

    char **str_list = str_multi_split(format_cpy, FORMATS, FORMAT_AMT);
    while (len <= SIZE && str_list[len] != NULL) { len ++; }

    va_start(args, __format);

    while (count < len) 
    {   
        char *curr_str = str_list[count];
        PrintFN(curr_str, va_arg(args, void *));
        free(curr_str);
        
        count++;
    }

    va_end(args);
    free(str_list); free(format_cpy);
}

void PrintFN(
    const char *restrict     __format, 
    ...
) 
{   
    va_list args;
    int count = 0;
    int len = 0;
    
    char final_str[1000] = "";
    char **str_list = str_multi_split(__format, FORMATS, FORMAT_AMT);
    while (len <= SIZE && str_list[len] != NULL) { len ++; }

    //printf("%s\n",__format);
    //PrintCArr(str_list, SIZE);

    va_start(args, __format);

    while (count < len) {
        char *curr_str = str_list[count];
        char format[5] = ""; char temp[1000] = "";

        size_t len = strlen(curr_str);

        sprintf(format, "%c%c", curr_str[len-2], curr_str[len-1]);
        
        /////   STRING
        if (strcmp(format, "%s") == 0) 
        {
            char *str = va_arg(args, char *);
            sprintf(temp, "%s%s%s%s", curr_str, "\b \b", "\b \b", str);
            goto FOUND;
        }

        /////   CHARACTER
        if (strcmp(format, "%c") == 0) 
        {
            char ch = va_arg(args, int);
            sprintf(temp, "%s%s%s%c", curr_str, "\b \b", "\b \b", ch);
            goto FOUND;
        }

        /////   INT
        if (strcmp(format, "%d") == 0) 
        {
            int d = va_arg(args, int);
            sprintf(temp, "%s%s%s%d", curr_str, "\b \b", "\b \b", d);
            goto FOUND;
        }

        /////   INT
        if (strcmp(format, "%i") == 0) 
        {
            int d = va_arg(args, int);
            sprintf(temp, "%s%s%s%d", curr_str, "\b \b", "\b \b", d);
            goto FOUND;
        }

        /////   PERCENT
        if (strcmp(format, "%%") == 0) 
        {
            sprintf(temp, "%s%s", curr_str, "\b \b");
            goto FOUND;
        }

        /////   NO FORMATS
        sprintf(temp, "%s", curr_str);
    FOUND:
        strcat(final_str, temp);
        free(curr_str);
        count++;
    }
    
    va_end(args);
    printf("%s", final_str);

    //prnt.Lists[prnt.Length] = (List)
    //{
    //    .Strings = {final_str},
    //    .Length = 1,
    //};
    prnt.Length++;
    free(str_list);
}

void PrintCArr(char **array, const int size) {
    for (int i = 0; i < size; i++) 
    {
        printf("[%d]\t\"%s\"\n", i, array[i]);
    }   
}

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "strexten.h"
#include "strstuff.h"

typedef struct {
    char *Strings[SIZE];
    unsigned Length;
} List;

typedef struct {
    List Lists[100];
    unsigned Length;
} Block;

Block printed = {
    .Lists = {},
    .Length = 0,
};


void DPrint(void);
void RPrintF(const char *restrict __format,...);
void PrintFNL(const char *restrict __format, ...);
void PrintFN(const char *restrict __format, ...);
void PrintCArr(char **array, const int __size);

int BlockAdd(Block *block, char **string_list);
int BlockRemove(Block *block);
int BlockReplace(Block *block, char **string_list);



// delete print
void DPrint(void) 
{
    int oldstr_list_len = BlockRemove(&printed);

    ///////// DELETE PREVIOUS PRINTED TEXT
    for (int i = 0; i < oldstr_list_len; i++) 
    {
        printf("\033[1A\r\033[2K");
    }
}





/*
ill figure out a way to implement this properly 
because i cant transfer variadic args all at once
*/ 
void RPrintF(
    const char *restrict    __format,
    ...
) 
{
    va_list args;
    int count = 0;
    int len = 0;
    
    char final_str[1000] = "";
    
    char **spliced_list = str_multi_split(__format, FORMATS, FORMAT_AMT);
    while (len <= SIZE && spliced_list[len] != NULL) { len ++; }

    va_start(args, __format);

    while (count < len) {
        char *curr_str = spliced_list[count];
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
            int i = va_arg(args, int);
            sprintf(temp, "%s%s%s%i", curr_str, "\b \b", "\b \b", i);
            goto FOUND;
        }

        /////   UNSIGNED INT
        if (strcmp(format, "%u") == 0) 
        {
            unsigned u = va_arg(args, unsigned);
            sprintf(temp, "%s%s%s%u", curr_str, "\b \b", "\b \b", u);
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

    char **final_list = str_multi_split(
        final_str, 
        (const char *[1]){"\n"}, 
        1
    );
    int oldstr_list_len = BlockReplace(&printed, final_list);
    
    ///////// DELETE PREVIOUS PRINTED TEXT
    for (int i = 0; i < oldstr_list_len; i++) 
    {
        printf("\033[1A\r\033[2K");
    }

    printf("%s", final_str);
    
    free(spliced_list); free(final_list);
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
    
    char **spliced_list = str_multi_split(__format, FORMATS, FORMAT_AMT);
    while (len <= SIZE && spliced_list[len] != NULL) { len ++; }

    va_start(args, __format);

    while (count < len) {
        char *curr_str = spliced_list[count];
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
            int i = va_arg(args, int);
            sprintf(temp, "%s%s%s%i", curr_str, "\b \b", "\b \b", i);
            goto FOUND;
        }

        /////   UNSIGNED INT
        if (strcmp(format, "%u") == 0) 
        {
            unsigned u = va_arg(args, unsigned);
            sprintf(temp, "%s%s%s%u", curr_str, "\b \b", "\b \b", u);
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

    char **final_list = str_multi_split(
        final_str, 
        (const char *[1]){"\n"}, 
        1
    );
    BlockAdd(&printed, final_list);
    
    free(spliced_list); free(final_list);
}

void PrintCArr(char **array, const int size) {
    for (int i = 0; i < size; i++) 
    {
        printf("[%d]\t\"%s\"\n", i, array[i]);
    }   
}

int BlockAdd(Block *block, char **string_list) 
{   
    if (block->Length >= 100) { puts("BLOCK OVERFLOW!"); exit(1); }
    int len = 0;
    while (len < SIZE && string_list[len] != NULL) 
    {   
        List *l = &block->Lists[block->Length];
        l->Strings[len] = string_list[len]; 
        len++;
        l->Length = len;
    }

    block->Lists[block->Length].Length = len;
    block->Length++;
    //printf("BLOCK LENGTH:\t%d\n", block->Length);
    //PrintCArr(block->Lists[block->Length-1].Strings, SIZE);
    return len;
}

int BlockRemove(Block *block) 
{
    if (block->Length == 0) { return 0; }
    int latest_list = block->Length - 1;
    int old_list_len = block->Lists[latest_list].Length;
    int len = 0;

    while (len < SIZE) 
    {   
        List *l = &block->Lists[latest_list];
        free(l->Strings[len]);
        len++;
    }
    
    //*(block->Lists + block->Length) = (List){};
    block->Length--;
    return old_list_len;
}

int BlockReplace(Block *block, char **string_list) 
{   
    if (block->Length == 0) { BlockAdd(block, string_list); return 0; }
    int latest_list = block->Length - 1;
    int old_list_len = block->Lists[latest_list].Length;
    int len = 0;

    while (len < SIZE && string_list[len] != NULL) 
    {   
        List *l = &block->Lists[latest_list];
        free(l->Strings[len]);

        l->Strings[len] = string_list[len];
        len++;
        l->Length = len;
    }
    //printf("BLOCK LENGTH:\t%d\n", block->Length);
    //PrintCArr(block->Lists[latest_list].Strings, SIZE);
    return old_list_len;
}

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strstuff.h"

// im addicted to reinventing the wheel (too lazy to search (please fucking help me))

char *strchar(
    const char *    __haystack, 
    const char      __needle
)
{   
    size_t len_hay = strlen(__haystack);
    char *cpy = strdup(__haystack);
    
    int i = 0;
    while (1) 
    {   
        if (__haystack[i] == '\0') { free(cpy); return NULL; }
        else if (__haystack[i] != __needle) { i++; continue; }
        
        int j = 0;
        while (1)
        {   
            if (__haystack[i+j] == '\0') 
            { 
                cpy[j] = '\0';
                break; 
            }

            cpy[j] = __haystack[i+j];
            j++;
        }

        break;
    }
    
    return cpy;
};

char *strcomp(
    const char *    __haystack, 
    const char *    __needle
)
{
    size_t len = strlen(__needle);
    if (len == 0) 
    {   
        return strdup(__haystack);
    }
    else if (len == 1) 
    {
        return strchar(__haystack, __needle[0]);
    }
    else 
    {
        char *after_sep = strstr(__haystack, __needle);
        if (after_sep == NULL) { return NULL; } 
        else { return strdup(after_sep); }
    }
}


char *str_sep_after(
    char *                  __str, 
    const char *restrict    __separator
)
{   
    int len_needle = strlen(__separator);

    char *str_cpy = strdup(__str);
    char *final = calloc(sizeof(char), strlen(str_cpy));
    if (final == NULL) { puts("[str_sep_after] calloc failed!"); exit(1); }

    char *after_sep = strcomp(str_cpy, __separator);
    if (after_sep == NULL) 
    { 
        free(final); 
        return NULL; 
    }
    //puts("======================");
    //printf("STR:\t\t\"%s\"\n", str_cpy);
    //printf("FOUND:\t\t\"%s\"\n", after_sep);

    ////////////////    copy till offset
    int offset = (strlen(str_cpy) - strlen(after_sep)) + len_needle;
    for (int i = 0; i < offset; i++) { final[i] = str_cpy[i]; }
    if (strlen(final) == 0) {
        free(final); 
        return NULL;
    }
    //printf("OFFSET:\t\t%d\n", offset);
    //printf("FINAL:\t\t\"%s\"\n", final);

    ////////////////
    strcpy(str_cpy, after_sep);
    //printf("STR = AFTER_SEP:\t\"%s\"\n", str_cpy);

    ////////////////    remove separator from str_cpy
    size_t len_new_str = strlen(str_cpy) - len_needle;
    //printf("LEN NEW STR:\t\t\"%zu\"\n", len_new_str);
    if (len_new_str != 0) 
    {
        char temp[len_new_str];
        int i = len_needle; 

        while (i < strlen(str_cpy)) 
        {   
            temp[i-len_needle] = str_cpy[i]; 
            i++;
        }   temp[i-len_needle] = '\0';
        
        strcpy(__str, temp);
        //printf("__str:\t\"%s\"\n", __str);
    }
    else 
    {
        strcpy(__str, "");
        //printf("__str:\t\"%s\"\n", __str);
    }


    free(str_cpy); free(after_sep);
    return final;
}


char **str_split(
    const char *restrict    __str, 
    const char *restrict    __separator
) 
{
    int occupied = 0;
    char **str_list = calloc(sizeof(char*), SIZE);
    if (str_list == NULL) { puts("[str_split] calloc failed!"); exit(1); }
    
    for (int i = 0; i < SIZE && str_list[i] != NULL; i++) {
        printf("[%d]\t\"%s\"\n", i, str_list[i]);
    }

    char *src = strdup(__str);
    if (src == NULL) { puts("[str_split] (src) calloc failed!"); exit(1); }

    do 
    {   
        char *token = str_sep_after(src, __separator);
        str_list[occupied] = token;

        if (token == NULL) 
        {      
            if (strlen(src) == 0) { str_list[occupied] = NULL; break; }
            else 
            {
                char *temp = strdup(src);
                if (temp == NULL) { puts("[str_split] (temp) calloc failed!"); exit(1); }
                str_list[occupied] = temp;
                break;
            }
        }

        occupied++;
    } while (1);


    //puts("======================");
    //printf("\"%s\"\n",__str);
    //printf("\"%s\"\n",__separator);
    //for (int i = 0; i < SIZE; i++) 
    //{
    //    printf("[%d]\t\"%s\"\n", i, str_list[i]);
    //}   

    free(src);
    return str_list;
}


char **multi_str_split(
    const char **restrict   __srcs, 
    const char *restrict    __separator
) 
{
    char **str_list = calloc(sizeof(char*), SIZE);
    if (str_list == NULL) { puts("[multi_str_split] calloc failed!"); exit(1); }

    int i = 0; int count = 0;
    while (__srcs[i] != NULL)
    {
        char **result = str_split((char *)__srcs[i], __separator);
        int j = 0;

        while (result[j] != NULL)
        {   
            str_list[count] = result[j];
            j++; count++;
        }

        free(result);
        i++;
    }
    
    return str_list;
}


char **str_multi_split(
    const char *restrict    __src, 
    const char **           __separators, 
    const int               __sep_capacity
) 
{
    const char **str_list = calloc(sizeof(char *), 1);
    if (str_list == NULL) { puts("[str_multi_split] calloc failed!"); exit(1); }
    
    char src_cpy[strlen(__src)]; strcpy(src_cpy, __src);
    str_list[0] = src_cpy;
    
    int i = 0;
    char **list_of_list[SIZE];
    list_of_list[i] = multi_str_split(str_list, __separators[0]);
    free(str_list);

    for (int j = 1; j < __sep_capacity; j++) 
    {
        list_of_list[i+1] = multi_str_split((const char **)list_of_list[i], __separators[j]);
        i++;
    }

    for (int j = 0; j < i; j++) { free(list_of_list[j]); }
    return list_of_list[i];
}
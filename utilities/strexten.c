#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strstuff.h"



// Separates a string into two after the word (separator)
char *str_sep_after(char *str, const char *restrict separator)
{   
    int len_needle = strlen(separator);

    char *str_cpy = strdup(str);
    char *final = calloc(sizeof(char), strlen(str_cpy));
    if (final == NULL) { puts("[str_sep_after] calloc failed!"); exit(1); }

    char *after_sep = strstr(str_cpy, separator);
    if (!after_sep) 
    { 
        free(final); 
        return NULL; 
    }
    //printf("STR:\t\t%s\n", str_cpy);
    //printf("FOUND:\t\t%s\n", after_sep);

    ////////////////    copy till offset
    int offset = (after_sep - str_cpy) + len_needle;
    for (int i = 0; i < offset; i++) { final[i] = str_cpy[i]; }
    //printf("FINAL:\t\t%s\n", final);

    ////////////////
    strcpy(str_cpy, after_sep);
    //printf("STR = AFTER_SEP:\t%s\n", str_cpy);

    ////////////////    remove separator from str_cpy
    char *temp = calloc(sizeof(char), strlen(str_cpy) - len_needle);
    if (temp == NULL) { puts("[str_sep_after] calloc failed!"); exit(1); }

    for (int i = len_needle; i < strlen(str_cpy); i++) 
    { 
        temp[i-len_needle] = str_cpy[i]; 
    }

    strcpy(str, temp);

    free(temp); free(str_cpy);
    return final;
}


/* Splits the string into multiple parts by the separator.
MAX SIZE 20*/
char **str_split(const char *restrict str, const char *restrict separator) {
    int occupied = 0;
    char **str_list = calloc(sizeof(char*), SIZE);
    if (str_list == NULL) { puts("[str_split] calloc failed!"); exit(1); }
    
    for (int i = 0; i < SIZE && str_list[i] != NULL; i++) {
        printf("[%d]\t\"%s\"\n", i, str_list[i]);
    }

    char *src = strdup(str);
    if (src == NULL) { puts("[str_split] (src) calloc failed!"); exit(1); }

    do 
    {   
        char *token = str_sep_after(src, separator);
        str_list[occupied] = token;

        if (token == NULL) 
        {   
            char *temp = strdup(src);
            if (temp == NULL) { puts("[str_split] (temp) calloc failed!"); exit(1); }
            str_list[occupied] = temp;
            break; 
        }

        occupied++;
    } while (1);

    free(src);
    return str_list;
}

/* Splits a list of strings into multiple parts by the separator.
MAX SIZE 20*/
char **multi_str_split(const char **restrict srcs, const char *restrict separator) {
    char **str_list = calloc(sizeof(char*), SIZE);
    if (str_list == NULL) { puts("[multi_str_split] calloc failed!"); exit(1); }

    int i = 0; int count = 0;
    while (srcs[i] != NULL)
    {
        char **result = str_split((char *)srcs[i], separator);
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

// FOR NOW, IT DOESNT USE THE SECOND ARGUMENT
char **str_multi_split(const char *restrict src, const char **separators) {
    const char **str_list = calloc(sizeof(char *), 1);
    if (str_list == NULL) { puts("[str_multi_split] calloc failed!"); exit(1); }
    
    char src_cpy[strlen(src)]; strcpy(src_cpy, src);
    str_list[0] = src_cpy;
    
    int i = 0;
    char ***list_of_list = calloc(sizeof(char *), SIZE);
    list_of_list[i] = multi_str_split(str_list, FORMATS[0]);
    free(str_list);

    for (int j = 1; j < FORMAT_AMT; j++) 
    {
        list_of_list[i+1] = multi_str_split((const char **)list_of_list[i], FORMATS[j]);
        i++;
    }

    for (int j = 0; j < i; j++) { free(list_of_list[j]); }
    free(list_of_list);
    
    return list_of_list[i];
}
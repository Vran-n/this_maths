#pragma once



// Returns malloc'd string
char *strchar(
    const char *    __haystack, 
    const char      __needle
);

// Returns malloc'd string
char *strcomp(
    const char *    __haystack, 
    const char *    __needle
);

/* 
Separates a string into two after the word (separator)
NOTE: __str requires the string to be malloc'd (which is stupid i know)
*/ 
char *str_sep_after(
    char        *__str, 
    const char  *__separator
);

/* 
Splits the string into multiple parts by the separator.
MAX SIZE 20
*/
char **str_split(
    const char *restrict    __str, 
    const char *restrict  __separator
);

/*
Splits a list of strings into multiple parts by the separator.
MAX SIZE 20
*/
char **multi_str_split(
    const char **restrict   __srcs, 
    const char *restrict  __separator
);

// FOR NOW, THERE WILL BE A THIRD ARGUMENT FOR THE CAPACITY OF THE SEPARATORS
char **str_multi_split(
    const char *restrict    __src, 
    const char **           __separators, 
    const int               __sep_capacity
);
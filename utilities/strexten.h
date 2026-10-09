#pragma once

char *str_sep_after(char *str, const char *separator);
char **str_split(const char *restrict str, const char *restrict separator) ;
char **multi_str_split(const char **restrict srcs, const char *restrict separator);
char **str_multi_split(const char *restrict src, const char **separators);
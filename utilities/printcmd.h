#pragma once

/*
PrintFormatNewLine.
SUPPORTS: %s, %c, %d, %i
*/
//void PrintFNL(
//    const char *restrict    __format, 
//    ...
//);

/*
DeletePrint.
*/
void DPrint(void);

/*
RePrintFormat.
SUPPORTS: %s, %c, %d, %i
*/
void RPrintF(
    const char *restrict    __format,
    ...
);

/*
PrintFormatNew.
SUPPORTS: %s, %c, %d, %i
*/
void PrintFN(
    const char *restrict    __format, 
    ...
);

void PrintCArr(char **array, const int __size);
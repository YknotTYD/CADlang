/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** cads_to_cadbin.h;
*/

#ifndef CADLANG_ASM_COMPILER_H

    #define CADLANG_ASM_COMPILER_H

    #define INSTRUCTION_COUNT 13
    #define COLOR_ERR "\x1b[38;2;255;55;55m"

    #include <stdio.h>
    #include <string.h>

extern const char *instructions[INSTRUCTION_COUNT];

char **str_to_warray(char *str, int *warray_len, char *seps);
char **warray_dup(char **warray);
void free_warray(char **warray);

void parse(const char **file);

#endif

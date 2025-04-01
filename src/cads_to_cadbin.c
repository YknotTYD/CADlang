/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** cads_to_cadbin.c;
*/

#include "../include/cads_to_cadbin.h"

const char *instructions[INSTRUCTION_COUNT] = {
    "MOV", "JMP", "CALL", "RET", "CMP", "ADD", "SUB",
    "MULT", "DIV", "AND", "OR", "XOR", "NOT"
};

static int process_instruction(char **warray, int line_index)
{
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        if (strcmp(warray[0], instructions[i]) == 0) {
            return 0;
        }
    }
    printf(COLOR_ERR"Unexpected token '%s' on line %i.\n",
        warray[0], line_index + 1);
    return 1;
}

static int process_line(char **warray, const int len, const int line_index)
{
    (void)len;
    if (warray[0] == 0) {
        return 0;
    }
    if (warray[0][0] == '.') {
        if (warray[1]) {
            return process_instruction(&warray[1], line_index);
        }
    } else {
        return process_instruction(warray, line_index);
    }
    return 0;
}

void parse(const char **file)
{
    char **warray;
    int len;

    for (int i = 0; file[i]; i++) {
        warray = str_to_warray((char *)file[i], &len, ", \t\n");
        if (process_line(warray, len, i)) {
            break;
        }
        free_warray(warray);
    }
    return;
}

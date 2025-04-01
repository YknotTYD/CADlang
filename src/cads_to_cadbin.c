/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** cadasm_to_cadbin.c;
*/

#include "../include/cads_to_cadbin.h"

const char *instructions[INSTRUCTION_COUNT] = {
    "MOV", "JMP", "CALL", "RET", "CMP", "ADD", "SUB",
    "MULT", "DIV", "AND", "OR", "XOR", "NOT"
};

static void process_label(char **warray)
{
    (void)warray;
    return;
}

static void process_instruction(char **warray, int line_index)
{
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        if (strcmp(warray[0], instructions[i]) == 0) {
            return;
        }
    }
    printf("Unexpected token '%s' on line %i.\n", warray[0], line_index + 1);
    return;
}

static void process_line(char **warray, const int len, const int line_index)
{
    (void)len;
    if (warray[0] == 0) {
        return;
    }
    if (warray[0][0] == '.') {
        process_label(warray);
        if (warray[1]) {
            process_instruction(&warray[1], line_index);
        }
    } else {
        process_instruction(warray, line_index);
    }
    return;
}

void parse(const char **file)
{
    char **warray;
    int len;

    for (int i = 0; file[i]; i++) {
        warray = str_to_warray((char *)file[i], &len, ", \t\n");
        process_line(warray, len, i);
        free_warray(warray);
    }
    return;
}

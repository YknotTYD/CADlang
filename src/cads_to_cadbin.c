/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** cads_to_cadbin.c;
*/

#include "../include/cads_to_cadbin.h"

const char *instructions[INSTRUCTION_COUNT] = {
    "MOV", "JMP",
    "CALL", "RET",
    "CMP", "ADD",
    "SUB", "MULT",
    "DIV", "AND",
    "OR", "XOR",
    "NOT"
};

const int operands[INSTRUCTION_COUNT][MAX_OPERAND_COUNT] = {
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_NONE}, //MOV
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //JMP  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //CALL TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //RET  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //CMP  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //ADD  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //SUB  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //MULT TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //DIV  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //AND  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //OR   TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //XOR  TODO: it
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE}    //NOT  TODO: it
};

static int process_operand(char *operand, int instindex,
    int opindex)
{
    if (operand[0] == 'R' && !(
        operands[instindex][opindex] & OPERAND_REGISTER)) {
        return 1;
    }
    if (operand[0] == '#' && !(
        operands[instindex][opindex] & OPERAND_DIRECT)) {
        return 1;
    }
    if (operand[0] == '[' && !(
        operands[instindex][opindex] & OPERAND_INDIRECT)) {
        return 1;
    }
    if (operand &&
        (operands[instindex][opindex] == OPERAND_NONE)) {
        return 1;
    }
    return 0;
}

static int process_operands(char **warray, int index, int line_index)
{
    for (int i = 0; i < MAX_OPERAND_COUNT; i++) {
        if (warray[i] == 0 && (operands[index][i] == OPERAND_NONE)) {
            return 0;
        }
        if (warray[i] == 0 && !(operands[index][i] == OPERAND_NONE)) {
            printf(ERR(ERRMSG_NEOP), instructions[index], line_index);
            return 1;
        }
        if (process_operand(warray[i], index, i)) {
            printf(ERR(ERRMSG_INVOP), i + 1, warray[i],
                instructions[index], line_index + 1);
            return 1;
        }
    }
    if (warray[MAX_OPERAND_COUNT]) {
        printf(ERR(ERRMSG_INVOP), MAX_OPERAND_COUNT + 1,
            warray[MAX_OPERAND_COUNT], instructions[index], line_index + 1);
        return 1;
    }
    return 0;
}

static int process_instruction(char **warray, int line_index)
{
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        if (strcmp(warray[0], instructions[i]) == 0) {
            return process_operands(&warray[1], i, line_index);
        }
    }
    printf(COLOR_ERR"Unknown instruction mnemonic '%s' on line %i.\n"
        COLOR_DEFAULT, warray[0], line_index + 1);
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

static void remove_comments_sub(char *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == COMMENT_CHAR) {
            line[i] = '\0';
            return;
        }
    }
    return;
}

static void remove_comments(char **file)
{
    for (int i = 0; file[i]; i++) {
        remove_comments_sub(file[i]);
    }
    return;
}

void parse(char **file)
{
    char **warray;
    int len;

    remove_comments(file);
    for (int i = 0; file[i]; i++) {
        warray = str_to_warray((char *)file[i], &len, ", \t\n");
        if (process_line(warray, len, i)) {
            free_warray(warray);
            break;
        }
        free_warray(warray);
    }
    return;
}

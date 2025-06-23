/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** parser.c;
*/

#include "../../include/cads_to_cadbin.h"

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
    {OPERAND_ANY, OPERAND_NONE, OPERAND_NONE},    //JMP
    {OPERAND_ANY, OPERAND_NONE, OPERAND_NONE},    //CALL
    {OPERAND_NONE, OPERAND_NONE, OPERAND_NONE},   //RET
    {OPERAND_ANY, OPERAND_ANY, OPERAND_NONE},     //CMP
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_ANY},  //ADD
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_ANY},  //SUB
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_ANY},  //MULT
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_ANY},  //DIV
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_ANY},  //AND
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_ANY},  //OR
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_ANY},  //XOR
    {~OPERAND_DIRECT, OPERAND_ANY, OPERAND_NONE}  //NOT
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

static int op_is_valid_sub(char *operand, int is_indirect)
{
    if (operand[0] == '\0') {
        return 0;
    }
    for (int i = 0; operand[i]; i++) {
        if (('0' <= operand[i] && operand[i] <= '9')) {
            continue;
        }
        if (operand[i] == '-') {
            continue;
        }
        if (is_indirect && operand[i] == ']' && operand[i + 1] == '\0') {
            return 1;
        }
        return 0;
    }
    return 1;
}

static int is_label(list_t *labels, char *operand, int line)
{
    (void)labels;
    if (operand[0] != '.') {
        return 0;
    }
    if (operand[1] == '\0') {
        printf(ERR(ERRMSG_EMPLBL), line);
        return 0;
    }
    for (node_t *current = labels->head; current; current = current->next) {
        if (my_strcmp(&operand[1], ((label_t *)current->data)->name) == 0) {
            return 1;
        }
    }
    printf(ERR(ERRMSG_UNKLBL), &operand[1], line);
    return 0;
}

static int op_is_valid(list_t *labels, char *operand, int line)
{
    switch (operand[0]) {
        case 'R':
            return op_is_valid_sub(&operand[1], 0);
        case '#':
            return op_is_valid_sub(&operand[1], 0) ||
                is_label(labels, &operand[1], line);
        case '[':
            if (operand[1] == '\0' || (operand[1] != '#' &&
                operand[1] != '#')) {
                return 0;
            }
            return op_is_valid_sub(&operand[2], 1) ||
                is_label(labels, &operand[2], line);
    }
    return 0;
}

static int process_operands(list_t *labels, char **warray,
    int index, int line_index)
{
    for (int i = 0; i < MAX_OPERAND_COUNT; i++) {
        if (warray[i] == 0 && (operands[index][i] == OPERAND_NONE))
            return 0;
        if (warray[i] == 0 && (operands[index][i] != OPERAND_NONE)) {
            printf(ERR(ERRMSG_NEOP), instructions[index], line_index);
            return 1;
        }
        if (!op_is_valid(labels, warray[i], line_index) ||
            process_operand(warray[i], index, i)) {
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

static int process_instruction(list_t *labels, char **warray, int line_index)
{
    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        if (strcmp(warray[0], instructions[i]) == 0) {
            return process_operands(labels, &warray[1], i, line_index);
        }
    }
    printf(ERR(ERRMSG_UNKINS), warray[0], line_index + 1);
    return 1;
}

static int process_line(list_t *labels, char **warray,
    const int len, const int line_index)
{
    (void)len;
    if (warray[0] == 0) {
        return 0;
    }
    if (warray[0][0] == '.') {
        if (warray[1]) {
            return process_instruction(labels, &warray[1], line_index);
        }
    } else {
        return process_instruction(labels, warray, line_index);
    }
    return 0;
}

int parse(list_t *labels, char **file)
{
    char **warray;
    int len;

    for (int i = 0; file[i]; i++) {
        warray = str_to_warray((char *)file[i], &len, ", \t\n");
        if (process_line(labels, warray, len, i)) {
            free_warray(warray);
            return 1;
        }
        free_warray(warray);
    }
    return 0;
}

/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** cads_to_cadbin.h;
*/

#ifndef CADLANG_ASM_COMPILER_H

    #define CADLANG_ASM_COMPILER_H

    #define COLOR_ERR     "\x1b[38;2;255;75;75m"
    #define COLOR_DEFAULT "\x1b[39m"

    #define ERRMSG_NEOP "Not enough operands for instruction %s on line %i.\n"
    #define ERRMSG_INVOP_SUB "Invald place %i operand '%s'"
    #define ERRMSG_INVOP ERRMSG_INVOP_SUB" for instruction %s on line %i.\n"
    #define ERRMSG_UNKINS "Unknown instruction mnemonic '%s' on line %i.\n"
    #define ERR(msg) (COLOR_ERR msg COLOR_DEFAULT)

    #define COMMENT_CHAR '/'

    #define INSTRUCTION_COUNT 13
    #define MAX_OPERAND_COUNT 3

    #define OPERAND_DIRECT   0b001
    #define OPERAND_INDIRECT 0b010
    #define OPERAND_REGISTER 0b100
    #define OPERAND_NONE     0b000
    #define OPERAND_ANY (OPERAND_DIRECT | OPERAND_INDIRECT | OPERAND_REGISTER)

    #include <stdio.h>
    #include <string.h>

extern const char *instructions[INSTRUCTION_COUNT];
extern const int operands[INSTRUCTION_COUNT][MAX_OPERAND_COUNT];

char **str_to_warray(char *str, int *warray_len, char *seps);
char **warray_dup(char **warray);
void free_warray(char **warray);

void parse(char **file);

#endif

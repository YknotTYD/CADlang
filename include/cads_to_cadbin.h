/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** cads_to_cadbin.h;
*/

#ifndef CADLANG_ASM_COMPILER_H

    #define CADLANG_ASM_COMPILER_H

    #define COLOR_ERR     "\x1b[38;2;255;75;75m"
    #define COLOR_DEFAULT "\x1b[39m\n"

    #define ERRMSG_NEOP "Not enough operands for instruction %s on line %i."
    #define ERRMSG_INVOP_SUB "Invalid place %i operand '%s'"
    #define ERRMSG_INVOP ERRMSG_INVOP_SUB" for instruction %s on line %i."
    #define ERRMSG_UNKINS "Unknown instruction mnemonic '%s' on line %i."
    #define ERRMSG_EMPLBL "Empty label on line %i."
    #define ERRMSG_INVLBL "Invalid label '%s' on line %i."
    #define ERRMSG_UNKLBL "Unknown label '%s' on line %i."
    #define ERRMSG_LBLERR "Label error on line %i."
    #define ERRMSG_DUPLBL "Duplicate label '%s' on line %i."
    #define ERRMSG_DUPLBLLINE "Duplicate label line pointing to ASM line %i."
    #define ERR(msg) (COLOR_ERR msg COLOR_DEFAULT)//COLOR_DEFAULT)

    #define COMMENT_CHAR '/'
    #define IS_ALPHA_LOWER(c) ((c) >= 'a' && (c) <= 'z')
    #define IS_ALPHA_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
    #define IS_NUM(c)         ((c) >= '0' && (c) <= '9')
    #define IS_ALPHA(c)       (IS_ALPHA_LOWER(c) || IS_ALPHA_UPPER(c))
    #define IS_ALNUM(c)       (IS_ALPHA(c) || IS_NUM(c))
    #define IS_LABEL_SUB(warray) ((warray)[0][0] == '.' && (warray)[1] == 0)
    #define IS_LABEL(warray) ((warray) && (warray[0]) && IS_LABEL_SUB(warray))

    #define INSTRUCTION_COUNT 13
    #define MAX_OPERAND_COUNT 3

    #define INT_SIZE 4
    #define MAX_VALUE_SIZE INT_SIZE

    #define OPERAND_DIRECT   0b001
    #define OPERAND_INDIRECT 0b010
    #define OPERAND_REGISTER 0b100
    #define OPERAND_NONE     0b000
    #define OPERAND_ANY (OPERAND_DIRECT | OPERAND_INDIRECT | OPERAND_REGISTER)

    #define OP_TO_CHAR "N#[ R"

    #define IID_MOV 0
    #define IID_JMP 1
    #define IID_CALL 2
    #define IID_RET 3
    #define IID_CMP 4
    #define IID_ADD 5
    #define IID_SUB 6
    #define IID_MULT 7
    #define IID_DIV 8
    #define IID_AND 9
    #define IID_OR 10
    #define IID_XOR 11
    #define IID_NOT 12

    #define SHEBANG "#!/usr/bin/env cadlang\n"
    #define SHEBANG_LEN 23

    #define VALUE_TO_INT(instruction, n) (*((int *)(instruction)->operand_values[(n)]))

    #include <stdio.h>
    #include <string.h>
    #include "lutils.h"
    #include "main.h"

typedef struct {
    char *name;
    int line;
} label_t;

typedef struct instruction_s{
    unsigned char iid;
    unsigned char operand_types[MAX_OPERAND_COUNT];
    unsigned char operand_values[MAX_OPERAND_COUNT][MAX_VALUE_SIZE];
} instruction_t;

typedef struct {
    char shebang[SHEBANG_LEN];
} header_t;

extern const char *instructions[INSTRUCTION_COUNT];
extern const int operands[INSTRUCTION_COUNT][MAX_OPERAND_COUNT];

char **str_to_warray(char *str, int *warray_len, char *seps);
char **warray_dup(char **warray);
void warray_remove_str(char **warray, int i);
void free_warray(char **warray);
int my_strcmp(char *str0, char *str1);
char **read_file(const char *filepath);
int my_getnbr(char *str, int *dest);
int my_memcpy(void *dest, void *src, int n);

void remove_comments(char **file);
void sanitize(char **file);
int parse_labels(cads_context_t *cads_context, char **file);
void free_labels(cads_context_t *cads_context);
int parse(list_t *labels, char **file);
int load_file(cads_context_t *cads_context, char **file);
void free_cads_context(cads_context_t *cads_context);

#endif

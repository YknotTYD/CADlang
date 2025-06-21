/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** load_file.c;
*/

#include "../../include/main.h"

void free_cads_context(cads_context_t *context)
{
    for (int i = 0; context->file[i]; i++) {
        free_warray(context->file[i]);
    }
    free(context->file);
    free_labels(context);
    for (node_t *crnt = context->opcodes->head; crnt; crnt = crnt->next) {
        free(crnt->data);
    }
    lutils.free_list(context->opcodes);

    return;
}

static void remove_labels(char ***file)
{
    for (int i = 0; file[i]; i++) {
        if (file[i] == 0 || IS_LABEL(file[i])) {
            free(file[i][0]);
            file[i][0] = 0;
            warray_remove_str((char **)file, i);
            i--;
            continue;
        }
        if (file[i][0][0] == '.' && file[i][1]) {
            warray_remove_str(file[i], 0);
        }
    }
    return;
}

//TODO: LOAD SMTHGELSTHN INTS
//TODO: HANDLE LABELS
static int copy_operand_value(unsigned char *value, char *token)
{
    
    int temp;

    if (my_getnbr(&token[1], &temp) || MAX_VALUE_SIZE != sizeof(int)) {
        return CATASTROPHIC_FAILURE;
    }
    printf("%i %s\n", temp, token);
    for (int i = 0; i < MAX_VALUE_SIZE; i++) {
        value[0] = ((char *)&temp)[i];
    }
    return 0;
}

static int append_code(list_t *opcodes, char **tokens)
{
    instruction_t *instruction = malloc(sizeof(instruction_t));

    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        if (my_strcmp(tokens[0], (char *)instructions[i]) == 0) {
            instruction->iid = i;
            break;
        }
    }
    tokens++;
    for (int i = 0; i < MAX_OPERAND_COUNT; i++) {
        instruction->operand_types[i] = OPERAND_NONE;
        for (int j = 0; j < MAX_VALUE_SIZE; j++) {
            instruction->operand_values[i][j] = 0;
        }
    }
    for (int i = 0; tokens[i]; i++) {
        if (tokens[i][0] == 'R')
            instruction->operand_types[i] =  OPERAND_REGISTER;
        else if (tokens[i][0] == '#')
            instruction->operand_types[i] =  OPERAND_DIRECT;
        else if (tokens[i][0] == '[')
            instruction->operand_types[i] =  OPERAND_INDIRECT;
        copy_operand_value(instruction->operand_values[i], tokens[i]);
    }
    lutils.append(opcodes, instruction);
    return 0;
}

int load_file(cads_context_t *context, char **file)
{
    char **warray;
    int len;

    for (len = 0; file[len]; len++);
    context->file = malloc(sizeof(char **) * (len + 1));
    for (int i = 0; file[i]; i++) {
        warray = str_to_warray(file[i], (int[]){0}, " \t,\n");
        context->file[i] = warray;
        context->file[i + 1] = 0;
    }
    remove_labels(context->file);
    context->opcodes = lutils.new_list();
    for (int i = 0; context->file[i]; i++) {
        append_code(context->opcodes, context->file[i]);
    }
    return 0;
}

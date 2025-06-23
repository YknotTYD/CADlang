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

static int get_token_value(char *token, int *n, list_t *labels);
static int get_indirect_token_value(char *token, int *n)
{
    int return_value;
    int len;
    int ends_with_it;

    for (len = 0; token[len]; len++);
    if (len <= 2) {
        return CATASTROPHIC_FAILURE;
    }
    ends_with_it = token[len - 1] == ']';
    if (ends_with_it) {
        token[len - 1] = '\0';
    }
    return_value = my_getnbr(&token[2], n);
    if (ends_with_it) {
        token[len - 1] = ']';
    }
    return return_value;
}

static int get_token_value(char *token, int *n, list_t *labels)
{
    if (token == 0) {
        return 1;
    }
    if (token[0] == '[') {
        return get_indirect_token_value(token, n);
    }
    if (token[1] != '.') {
        return my_getnbr(&token[1], n);
    }
    for (node_t *current = labels->head; current; current = current->next) {
        if (my_strcmp(((label_t *)current->data)->name, &token[2]) == 0) {
            *n = ((label_t *)current->data)->line;
            return 0;
        }
    }
    return 0;
}

//TODO: LOAD SMTHGELSTHN INTS
static int copy_operand_value(unsigned char *value, char *token,
    list_t *labels)
{    
    int temp;

    if (get_token_value(token, &temp, labels) || MAX_VALUE_SIZE != sizeof(int)) {
        return CATASTROPHIC_FAILURE;
    }
    for (int i = 0; i < MAX_VALUE_SIZE; i++) {
        value[i] = ((char *)&temp)[i];
    }
    return 0;
}

static int append_code(list_t *opcodes, char **tokens, list_t *labels)
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
        copy_operand_value(instruction->operand_values[i], tokens[i], labels);
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
        append_code(context->opcodes, context->file[i], context->labels);
    }
    return 0;
}

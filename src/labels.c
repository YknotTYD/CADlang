/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** labels.c;
*/

#include "../include/cads_to_cadbin.h"

static int is_valid_label(char *target)
{
    if (!IS_ALPHA(target[0])) {
        return 0;
    }
    for (int i = 0; target[i]; i++) {
        if (IS_ALNUM(target[i]) || target[i] == '_') {
            continue;
        }
        if (target[i] == ':' && target[i + 1] == '\0') {
            continue;
        }
        return 0;
    }
    return 1;
}

static int look_for_label(cads_context_t *cads_context, char *target, int line)
{
    label_t *label;

    if (target == 0 || target[0] == '\0' || target[0] != '.')
        return 0;
    if (target[1] == '\0' || target[1] == ':') {
        printf(ERR(ERRMSG_EMPLBL), line + 1);
        return 1;
    }
    if (!is_valid_label(&target[1])) {
        printf(ERR(ERRMSG_INVLBL), target, line);
        return 1;
    }
    label = malloc(sizeof(label_t));
    label->name = strdup(&target[1]);
    if (label->name[strlen(label->name) - 1] == ':') {
        label->name[strlen(label->name) - 1] = '\0';
    }
    label->line = line;
    lutils.append(cads_context->labels, label);
    return 0;
}

void free_labels(cads_context_t *cads_context)
{
    for (node_t *current = cads_context->labels->head; current;
        current = current->next) {
        free(((label_t *)(current->data))->name);
        free(current->data);
    }
    lutils.free_list(cads_context->labels);
    return;
}

int parse_labels(cads_context_t *cads_context, char **file)
{
    char **warray;
    int len;

    for (int i = 0; file[i]; i++) {
        warray = str_to_warray(file[i], &len, " \t,\n");
        if (look_for_label(cads_context, warray[0], i)) {
            free_warray(warray);
            return 1;
        }
        free_warray(warray);
    }
    for (node_t *current = cads_context->labels->head; current;
        current = current->next) {
        printf("[%s] %i\n", ((label_t *)current->data)->name,
            ((label_t *)current->data)->line);
    }
    return 0;
}

/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** labels.c;
*/

#include "../../include/cads_to_cadbin.h"

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

static int get_label_line(char **warray, int line)
{
    if (warray[0] == 0) {
        printf(ERR(ERRMSG_LBLERR), line);
        return -1;
    }
    if (warray[1] == 0) {
        return line + 1;
    }
    return line;
}

static void append_label(list_t *list, char *name, int line)
{
    label_t *label;

    label = malloc(sizeof(label_t));
    label->name = strdup(name);
    if (label->name[strlen(label->name) - 1] == ':') {
        label->name[strlen(label->name) - 1] = '\0';
    }
    label->line = line;
    lutils.append(list, label);
    return;
}

static int is_duplicate_label(cads_context_t *cads_context,
    char *label, int line)
{
    int cmp;

    for (node_t *current = cads_context->labels->head; current;
        current = current->next) {
        cmp = my_strcmp(label, ((label_t *)current->data)->name);
        if (cmp == 0 || cmp == ':') {
            printf(ERR(ERRMSG_DUPLBL),
                ((label_t *)current->data)->name, line + 1);
            return 1;
        }
    }
    return 0;
}

static int look_for_label(cads_context_t *cads_context, char *target,
    int line, char **warray)
{
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
    if (is_duplicate_label(cads_context, &target[1], line)) {
        return 1;
    }
    append_label(cads_context->labels, &target[1],
        get_label_line(warray, line));
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
        if (look_for_label(cads_context, warray[0], i, warray)) {
            free_warray(warray);
            return 1;
        }
        free_warray(warray);
    }
    return 0;
}

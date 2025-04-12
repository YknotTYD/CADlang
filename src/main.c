/*
** EPITECH PROJECT, 2024
** CADlang
** File description:
** main.c;
*/

#include "../include/main.h"

//put error messages in stderr;
//make str_to_warray take consts;
//get it on snap;
//add a docs site;
//add MOVB;
//add labels to compilation;
//make error messages red when !isatty;
//make it so that two labels can't belong to the same line;
//add error handling for labels pointing on nothing;

static int parse_error(cads_context_t *cads_context, char **file)
{
    cads_context->labels = lutils.new_list();
    if (parse_labels(cads_context, file)) {
        free_warray(file);
        free_labels(cads_context);
        return 1;
    }
    if (parse(file)) {
        free_warray(file);
        free_labels(cads_context);
        return 1;
    }
    free_labels(cads_context);
    return 0;
}

static int is_duplicate_line(label_t *label, list_t *labels)
{
    for (node_t *current = labels->head; current; current = current->next) {
        if (label != current->data &&
            label->line == ((label_t *)current->data)->line) {
            return 1;
        }
    }
    return 0;
}

static int parse_non_error(cads_context_t *cads_context, char **file)
{
    cads_context->labels = lutils.new_list();
    sanitize(file);
    if (parse_labels(cads_context, file)) {
        free_warray(file);
        free_labels(cads_context);
        return 1;
    }
    for (node_t *current = cads_context->labels->head; current;
        current = current->next) {
        printf("%s %i\n", ((label_t *)current->data)->name,
            ((label_t *)current->data)->line);
        if (is_duplicate_line(current->data, cads_context->labels)) {
            dprintf(2, ERR(ERRMSG_DUPLBLLINE),
                ((label_t *)current->data)->line + 1);
            free_warray(file);
            free_labels(cads_context);
            return 84;
        }
    }
    return 0;
}

static int load_and_check(char ***file, int argc, char **argv)
{
    if (argc < 2) {
        printf(ERR(ERRMSG_NEARGS));
        return 1;
    }
    *file = read_file(argv[1]);
    if (*file == 0) {
        printf(ERR(ERRMSG_FILERR), argv[1]);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    char **file = 0;
    cads_context_t cads_context;

    if (load_and_check(&file, argc, argv))
        return 84;
    remove_comments(file);
    if (parse_error(&cads_context, file) ||
        parse_non_error(&cads_context, file))
        return 84;
    load_file(&cads_context, file);
    free_cads_context(&cads_context);
    free_warray(file);
    return 0;
}

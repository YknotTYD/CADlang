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
//add MOVB
//make error messages red when !isatty;

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

static int parse_non_error(cads_context_t *cads_context, char **file)
{
    cads_context->labels = lutils.new_list();
    sanitize(file);
    if (parse_labels(cads_context, file)) {
        free_warray(file);
        free_labels(cads_context);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    char **file = 0;
    cads_context_t cads_context;

    if (argc < 2) {
        printf(ERR(ERRMSG_NEARGS));
        return 84;
    }
    file = read_file(argv[1]);
    if (file == 0) {
        printf(ERR(ERRMSG_FILERR), argv[1]);
        return 84;
    }
    remove_comments(file);
    if (parse_error(&cads_context, file))
        return 84;
    if (parse_non_error(&cads_context, file))
        return 84;
    free_warray(file);
    free_labels(&cads_context);
    return 0;
}
